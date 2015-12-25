#include "icmekan.h"
#include "ui_icmekan.h"
#include "Graph.h"
#include <QGraphicsItemGroup>
#include <QTextStream>

#define MAPPATH "C:/Users/test/Documents/GitHub/Group6Interface/seyda.jpg"
#define DMWIDTH 35 // Destination Marker Width
#define NLWIDTH 15 // Node Location Marker Width
#define DEVELOPERMODE true


IcMekan::IcMekan(QWidget *parent) :
    QDialog(parent),
    Iui(new Ui::IcMekan)
{
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);

    Area point1 (20, 12, 215, 178);
    colorAreaPoint.push_back(point1);
    Area point2(20, 184, 240, 185);
    colorAreaPoint.push_back(point2);
    Area point3 (32, 375, 230, 137);
    colorAreaPoint.push_back(point3);
    Area point4 (20, 510, 250, 180);
    colorAreaPoint.push_back(point4);
    Area point5 (260, 510, 200, 145);
    colorAreaPoint.push_back(point5);
    Area point6 (460, 510, 240, 180);
    colorAreaPoint.push_back(point6);
    Area point7 (420, 380, 280, 140);
    colorAreaPoint.push_back(point7);
    Area point8 (456, 189, 260, 190);
    colorAreaPoint.push_back(point8);
    Area point9 (518, 12, 180, 190);
    colorAreaPoint.push_back(point9);
    Area point10 (392, 16, 125, 180);
    colorAreaPoint.push_back(point10);
    Area point11 (215, 16, 185, 180);
    colorAreaPoint.push_back(point11);


    int xMiddle,yMiddle;


    for(int i=0;i<colorAreaPoint.size();i++)
    {
        xMiddle=colorAreaPoint.at(i).x + (colorAreaPoint.at(i).width)*0.5;
        yMiddle=colorAreaPoint.at(i).y + (colorAreaPoint.at(i).height)*0.5;

        NodeCoordinate.push_back(Coor(xMiddle,yMiddle));
    }
    //QTextStream(stdout) << NodeCoordinate.size() << endl;

    //Add Vertex

    /*for(int i=0;i<NodeCoordinate.size();i++)
    {
        g.addVertex(NodeCoordinate.at(i));
    }*/


    WayCoordinate.push_back(Coor(208,142));
    WayCoordinate.push_back(Coor(227,267));
    WayCoordinate.push_back(Coor(227,443));
    WayCoordinate.push_back(Coor(227,590));
    WayCoordinate.push_back(Coor(349,602));
    WayCoordinate.push_back(Coor(488,579));
    WayCoordinate.push_back(Coor(487,456));
    WayCoordinate.push_back(Coor(487,300));
    WayCoordinate.push_back(Coor(534,137));
    WayCoordinate.push_back(Coor(451,118));
    WayCoordinate.push_back(Coor(324,122));

    QTextStream(stdout) << WayCoordinate.size() << endl;

    //Add Vertex

    for(int i=0;i<WayCoordinate.size();i++)
    {
        g.addVertex(WayCoordinate.at(i));
    }



    vector<Vertex> vertexList;
    vertexList=g.getVertexList();



    g.setEdge(vertexList[0],vertexList[1]);
    g.setEdge(vertexList[1],vertexList[2]);
    g.setEdge(vertexList[1],vertexList[3]);
    /*
    g.add(Coor(150,165),Coor(180,164));
    g.add(Coor(180,164),Coor(179,133));
    g.add(Coor(179,133),Coor(226,165));
    g.add(Coor(226,165),Coor(223,203));
    g.add(Coor(198,201),Coor(223,203));
    g.add(Coor(220,360),Coor(223,203));

    // Get Edge List Must Be Implemented
    // Shortest Path Must Return Edge List
    */

    Iui->setupUi(this);
    scene = new QGraphicsScene(this);
    Iui->graphicsView->setScene(scene);

    blackPen.setWidth(6);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(MAPPATH));



    // Create Destination Marker on map
    destinationMarker = scene -> addEllipse(0,0,DMWIDTH,DMWIDTH,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    destinationVertex = g.addVertex(Coor(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2));
    connectToServer();
    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    locationMarker->setRotation(input_s.d*-1);
    locationVertex = g.addVertex(Coor(locationMarker->pos().x(), locationMarker->pos().y()));

    // Create Node Locations Marker
    if(DEVELOPERMODE)
    {
        // Draw lines between all vertexes
        /*vector<Edge> edgeList = g.getAllEdge();
        for(uint i = 0; i < edgeList.size()-1; ++i)
        {
            // Add Line for Edges
            drawLine(edgeList[i].getSourceVertex(), edgeList[i].getDestVertex(), blackPen);
        }*/

        for(uint i = 0; i < vertexList.size(); ++i)
        {
            nodeLocationsMarker = scene -> addEllipse(vertexList[i].getX()-NLWIDTH/2,
                                                      vertexList[i].getY()-NLWIDTH/2,
                                                      NLWIDTH,
                                                      NLWIDTH,
                                                      blackPen,
                                                      greenBrush);
        }
    }
    /*
    // Draw lines between all vertexes
    for(uint i = 0; i < vertexList.size()-1; ++i)
    {
        // Add Line for Edges
        drawLine(vertexList[i],vertexList[i+1] );

    }
    */
    //seekLocation();

    time=new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(update2()));
    time->start(1000);
}



IcMekan::~IcMekan()
{
    delete Iui;
    ::close(socketDescriptor);
}

void IcMekan::on_pushButton_clicked()
{
    // Print destination location
    //ui->label->setText(QString::number(destinationMarker->pos().x()+ DMWIDTH/2) + ", " + QString::number(destinationMarker->pos().y()+ DMWIDTH/2));

    QPen redPen(Qt::red);
    redPen.setWidth(5);

    destinationVertex->setVertex(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2);
    locationVertex->setVertex(locationMarker->pos().x() + 10, locationMarker->pos().y());

    Iui->label->setText("destination vertex = " + QString::number(destinationVertex->getX()) + ", " + QString::number(destinationVertex->getY()));

    clearLines();

    QGraphicsLineItem *line;
    /*line = drawLine(*locationVertex, g.getVertexList()[0], redPen);
    drawedLines.push_front(line);
    for(uint i = 0; i < g.getVertexList().size()-3; ++i)
    {
        // Add Line for Edges
        line = drawLine(g.getVertexList()[i], g.getVertexList()[i+1], redPen);
        drawedLines.push_front(line);
    }
    line = drawLine(*destinationVertex, g.getVertexList()[g.getVertexList().size()-3], redPen);
    drawedLines.push_front(line);*/
    //locationMarker->setRotation(45);
    veri=FindArea();
    destinationRect=veri;


    QPixmap pix(1000,1000);

    pix.fill(Qt::transparent);

    QPainter painter(&pix);

    painter.setBrush(QColor(0, 255, 0, 127));

    xTransRect=colorAreaPoint.at(veri).x;
    yTransRect=colorAreaPoint.at(veri).y;
    widthTransRect=colorAreaPoint.at(veri).width;
    heightTransRect=colorAreaPoint.at(veri).height;


    rect.setRect(xTransRect, yTransRect,widthTransRect ,heightTransRect);

    painter.drawRect(rect);

    scene -> addPixmap(pix);
}

void IcMekan::seekLocation()
{
    Iui->label->setText("Seeking User Location...");
    // Get location from hardware
}


QGraphicsLineItem* IcMekan::drawLine(Vertex &c1, Vertex &c2, QPen pen)
{
     return scene -> addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),pen);
}

void IcMekan::clearLines()
{
    for(int i = 0; i < drawedLines.size(); ++i)
    {
        scene->removeItem(drawedLines[i]);
        scene->update();
    }
}
int IcMekan::FindArea()
{
    QTextStream(stdout) << "size" << colorAreaPoint.size() << endl;

    for(int i=0;i<colorAreaPoint.size();i++)
    {
        // && (destinationVertex->getY()< colorAreaPoint.at(i).y) && (destinationVertex->getX() < ( colorAreaPoint.at(i).width +colorAreaPoint.at(i).x ))  &&  (destinationVertex->getY() < ( colorAreaPoint.at(i).height +colorAreaPoint.at(i).y ))

        if( destinationVertex->getX() >= colorAreaPoint.at(i).x)
        {
            if(destinationVertex->getY() >= colorAreaPoint.at(i).y)
            {
                if(destinationVertex->getX()< ( colorAreaPoint.at(i).width +colorAreaPoint.at(i).x ))
                {
                    if(destinationVertex->getY()< ( colorAreaPoint.at(i).height +colorAreaPoint.at(i).y))
                    {
                        QTextStream(stdout) << i << endl;

                        QTextStream(stdout) << colorAreaPoint.at(i).x << endl;

                        QTextStream(stdout) <<"Akilli x gelen " <<destinationMarker->pos().x() + DMWIDTH/2 << endl;
                        QTextStream(stdout) <<"Akilli x array " <<colorAreaPoint.at(i).x << endl;
                        QTextStream(stdout) <<"Akilli x width " <<colorAreaPoint.at(i).width +colorAreaPoint.at(i).x << endl;
                        QTextStream(stdout) <<"Akilli y array " <<colorAreaPoint.at(i).y << endl;
                        QTextStream(stdout) <<"Akilli y height " <<colorAreaPoint.at(i).height +colorAreaPoint.at(i).y << endl;
                        return i;
                    }
                }
            }

        }

    }
    QTextStream(stdout) <<"Disariii " << endl;
    /*QTextStream(stdout) <<"Salak x gelen " <<destinationVertex->getX() << endl;
    QTextStream(stdout) <<"Salak x array " <<colorAreaPoint.at(i).x << endl;
    QTextStream(stdout) <<"Salak x width " <<colorAreaPoint.at(i).width +colorAreaPoint.at(i).x << endl;
    QTextStream(stdout) <<"Salak y array " <<colorAreaPoint.at(i).y << endl;
    QTextStream(stdout) <<"Salak y height " <<colorAreaPoint.at(i).height +colorAreaPoint.at(i).y << endl;*/
    QTextStream(stdout) << destinationMarker->pos().x() + DMWIDTH/2 << endl;
    QTextStream(stdout) << destinationMarker->pos().y() + DMWIDTH/2 << endl;
    return 6;


}

void IcMekan::update2(){

    QPen blackPen(Qt::black);
    int angle= locationMarker->rotation();
    /*int x=locationMarker->pos().x;
    int y=locationMarker->pos().y;
*/
    char buf[LINE_ARRAY_SIZE];
    // Read the modified line back from the server.
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
        cerr << "didn't get response from server?";
        ::close(socketDescriptor);
        exit(1);
    }

    /*

     soft

     */
    input_s.setInput(string(buf));
    cerr << "Modified: " << buf << "\n";
    cerr << "x: " << input_s.x << " y:" << input_s.y << " d: " << input_s.d << " rec: " << input_s.rec <<  endl;
    int result;
    /*

     BURASI YAZILIMCILARIN ALANI
     GELEN DATA PARS EDİLECEK GEREKLİ İŞLEMLER YAPILACAK
     RESULT OLARAK 1 2 3 4 5 SAYILARINDAN BİRİSİ DÖNECEK

     */
    /*if (input_s.d < 10 || input_s.d > 350) {
        result = 2;
    } else if (input_s.d >= 10 && input_s.d < 180) {
        result = 3;
    } else {
        result = 1;
    }*/

    if(destinationRect!=-1)
    {
        for(int i=0;i<drawedLines.size();i++)
        {
            scene->removeItem(drawedLines.at(i));
        }

        veri=input_s.rec;
        cerr<<"-1 değil set edildi \n";

        //saat yönüne sol dedik

        int counterSag=0,counterSol=0;

        bool sol = true;
        bool sag = true;

        //Soldan giderken bulunun uzaklık
        for(int i=veri;i<=11 && sol == false ;i++)
        {
            counterSol++;
            if(veri==destinationRect){
                sol = false;
                break;
             }
        }
        cerr <<"counterSol1:"<<counterSol << endl;
        if(sol == true){
            for(int i=1; i<=destinationRect;i++)
            {
                counterSol++;
            }
         }
        cerr <<"counterSol2:"<<counterSol << endl;
        //Sağdan giderken bulunan uzaklık
        cerr << "veri:"<< veri << endl;
        cerr << "dest "<< destinationRect<<endl;
        for(int i=veri;i<=1 && sag == false;i--)
        {
            counterSag++;
            if(destinationRect == veri){
                sag = false;
                break;
            }
        }
        cerr <<"counterSag1:"<<counterSag << endl;
        if(sag == true){

            for(int i = 11;i>=destinationRect;i--){
                counterSag++;
            }

        }
        cerr <<"counterSag2:"<<counterSag << endl;

        //locationMarker->setPos(NodeCoordinate.at(input_s.rec-1).x,NodeCoordinate.at(input_s.rec-1).y);
        locationMarker->setPos(WayCoordinate.at(input_s.rec-1).x,WayCoordinate.at(input_s.rec-1).y);

        if(counterSag < counterSol)
        {
            cerr<<"Sollll !!!!!!!!"<<endl;
            for(int i=veri;i<=1 && sag == false;i--)
            {
                drawedLines.push_back(scene -> addLine(WayCoordinate.at(i).x,WayCoordinate.at(i).y,WayCoordinate.at(i-1).x,WayCoordinate.at(i-1).y,blackPen));
                if(destinationRect == veri){
                    sag = false;
                    break;
                }


            }
            cerr <<"counterSag1:"<<counterSag << endl;
            if(sag == true){
                drawedLines.push_back(scene -> addLine(WayCoordinate.at(0).x,WayCoordinate.at(0).y,WayCoordinate.at(10).x,WayCoordinate.at(10).y,blackPen));
                for(int i = 10;i>destinationRect;i--){
                    cerr<<"i: " << i<<"dest Rect"<<destinationRect<<endl;
                    drawedLines.push_back(scene -> addLine(WayCoordinate.at(i).x,WayCoordinate.at(i).y,WayCoordinate.at(i-1).x,WayCoordinate.at(i-1).y,blackPen));

                }

            }
            if(veri==1 || veri==9 ||veri==6 || veri==4)
            {
                //sola don
                //sprintf(sendData, "%d", 2);
                //sleep(1000);
                sprintf(sendData, "%d", 3);
            }
            else
            {
                //sprintf(sendData, "%d", 2);
                //sleep(1000);
                sprintf(sendData, "%d", 4);
            }


        }
        else
        {
            cerr<<"Saggg !!!!!!!!"<<endl;
            for(int i=veri-1;i<11 && sol == false ;i++)
            {

                drawedLines.push_back(scene -> addLine(WayCoordinate.at(i).x,WayCoordinate.at(i).y,WayCoordinate.at(i+1).x,WayCoordinate.at(i+1).y,blackPen));
                if(veri==destinationRect){
                    sol = false;
                    break;
                 }
            }
            cerr <<"counterSol1:"<<counterSol << endl;
            if(sol == true){
                //scene -> addLine(WayCoordinate.at(10).x,WayCoordinate.at(10).y,WayCoordinate.at(0).x,WayCoordinate.at(0).y,blackPen);
                for(int i=0; i<destinationRect;i++)
                {
                    drawedLines.push_back(scene -> addLine(WayCoordinate.at(i).x,WayCoordinate.at(i).y,WayCoordinate.at(i+1).x,WayCoordinate.at(i+1).y,blackPen));
                }
             }
            cerr <<"sag:" << counterSag << endl;

            if(veri==1 || veri==9 ||veri==6 || veri==4)
            {
                //sola don
                sprintf(sendData, "%d", 2);
                //sleep(1000);
                //sprintf(sendData, "%d", 1);
            }
            else
            {
                sprintf(sendData, "%d", 2);
                //sleep(1000);
                //sprintf(sendData, "%d", 4);
            }
        }
    }

    //sprintf(sendData, "%d", result);
    //strcat(buf, sendData);

    //strcat(buf, "****");
    //cerr << "Modified: " << buf << "\n";
    // Send the line to the server.
    if (send(socketDescriptor, sendData, 1 + 1, 0) < 0) {
        cerr << "cannot send data ";
        ::close(socketDescriptor);
        exit(1);
    }

    // Zero out the buffer.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.  As above.
    //cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;

    locationMarker->setRotation(input_s.d*-1);
    scene->update();
}

void IcMekan::connectToServer(){


    unsigned short int serverPort = 5005;
    struct sockaddr_in serverAddress;
    struct hostent *hostInfo;
    char buf[LINE_ARRAY_SIZE];
    WSADATA AAA;

    //cout << "Enter server host name or IP address: ";
    //cin.get(buf, MAX_LINE, '\n');

    // gethostbyname() takes a host name or ip address in "numbers and
    // dots" notation, and returns a pointer to a hostent structure,
    // which we'll need later.  It's not important for us what this
    // structure is actually composed of.
    WSAStartup(2,&AAA);
    hostInfo = gethostbyname("162.243.185.121");
    if (hostInfo == NULL) {
        cerr << WSAGetLastError() << endl;
        cout << "problem interpreting host: " << buf << "\n";
        exit(1);
    }

    //cout << "Enter server port number: ";
    //cin >> serverPort;
    //cin.get(c); // dispose of the newline

    // Create a socket.  "AF_INET" means it will use the IPv4 protocol.
    // "SOCK_STREAM" means it will be a reliable connection (i.e., TCP;
    // for UDP use SOCK_DGRAM), and I'm not sure what the 0 for the last
    // parameter means, but it seems to work.
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) {
        cerr << "cannot create socket\n";
        exit(1);
    }

    // Connect to server.  First we have to set some fields in the
    // serverAddress structure.  The system will assign me an arbitrary
    // local port that is not in use.
    serverAddress.sin_family = hostInfo->h_addrtype;
    memcpy((char *) &serverAddress.sin_addr.s_addr, hostInfo->h_addr_list[0],
            hostInfo->h_length);
    serverAddress.sin_port = htons(serverPort);

    if (::connect(socketDescriptor, (struct sockaddr *) &serverAddress,
            sizeof(serverAddress)) < 0) {
        cerr << WSAGetLastError() << endl;
        cerr << "cannot connect\n";
        exit(1);
    }

    cout << "\nEnter some lines, and the server will modify them and\n";
    cout << "send them back.  When you are done, enter a line with\n";
    cout << "just a dot, and nothing else.\n";
    cout << "If a line is more than " << MAX_LINE << " characters, then\n";
    cout << "only the first " << MAX_LINE << " characters will be used.\n\n";

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.
    cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;

    // Stop when the user inputs a line with just a dot.

    // Read the modified line back from the server.
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
        cerr << "didn't get response from server?";
        ::close(socketDescriptor);
        exit(1);
    }

    /*

     soft

     */
    input_s.setInput(string(buf));
    cerr << "Modified: " << buf << "\n";
    cerr << "x: " << input_s.x << " y:" << input_s.y << " d: " << input_s.d << " rec: " << input_s.rec <<  endl;
    int result;
    /*

     BURASI YAZILIMCILARIN ALANI
     GELEN DATA PARS EDİLECEK GEREKLİ İŞLEMLER YAPILACAK
     RESULT OLARAK 1 2 3 4 5 SAYILARINDAN BİRİSİ DÖNECEK

     */
    if (input_s.d < 10 || input_s.d > 350) {
        result = 2;
    } else if (input_s.d >= 10 && input_s.d < 180) {
        result = 3;
    } else {
        result = 1;
    }



    sprintf(sendData, "%d", result);
    //strcat(buf, sendData);

    //strcat(buf, "****");
    //cerr << "Modified: " << buf << "\n";
    // Send the line to the server.
    if (send(socketDescriptor, sendData, 1 + 1, 0) < 0) {
        cerr << "cannot send data ";
        ::close(socketDescriptor);
        exit(1);
    }

    // Zero out the buffer.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.  As above.
    //cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;


    //close(socketDescriptor);
}



void IcMekan::on_deneme_clicked()
{

    locationMarker->setRotation(30);

    locationMarker->setPos(30,40);
    //2 gönder

}

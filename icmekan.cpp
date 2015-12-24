#include "icmekan.h"
#include "ui_icmekan.h"
#include "Graph.h"
#include <QGraphicsItemGroup>
#include <QTextStream>

#define MAPPATH "C:/Users/test/Documents/Group6Interface/KatPlaniPP.jpg"
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


    Iui->setupUi(this);

    scene = new QGraphicsScene(this);
    Iui->graphicsView->setScene(scene);

    blackPen.setWidth(6);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(MAPPATH));



    // Create Destination Marker on map
    destinationMarker = scene -> addEllipse(0,0,DMWIDTH,DMWIDTH,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    //destinationVertex = g.addVertex(Coor(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2));


  //************  connectToServer();


    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    //locationVertex = g.addVertex(Coor(locationMarker->pos().x(), locationMarker->pos().y()));



    //painter.drawRect(20, 12, 215, 178); //1. bölge
    //painter.drawRect(20, 184, 240, 185); //2. bölge
    //painter.drawRect(32, 375, 230, 137); //3. bölge
    //painter.drawRect(20, 510, 250, 180); //4. bölge
    //painter.drawRect(260, 510, 200, 145); //5. bölge
    //painter.drawRect(460, 510, 240, 180); //6. bölge
    //painter.drawRect(420, 380, 280, 140); //7. bölge
    //painter.drawRect(456, 189, 260, 190); //8. bölge
    //painter.drawRect(518, 12, 180, 190); //9. bölge
    //painter.drawRect(392, 16, 125, 180); //10. bölge
    //painter.drawRect(215, 16, 185, 180); //11. bölge




   // Area point (0, 0, 0, 0);
   // colorAreaPoint.push_back(point);

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


    /*int x1;
    int x2;
    int y1;
    int y2;

    x1=colorAreaPoint.at(0).x;*/




    /*time=new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(update2()));
    time->start(1000);*/

}



IcMekan::~IcMekan()
{
    delete Iui;
    ::close(socketDescriptor);
}

void IcMekan::on_pushButton_clicked()
{
    //Iui->label->setText("AAAAAAAAA");
    QPen redPen(Qt::red);
    redPen.setWidth(5);

    //destinationVertex->setVertex(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2);
    //locationVertex->setVertex(locationMarker->pos().x() + 10, locationMarker->pos().y());

    Iui->label->setText("destination vertex = " + QString::number(destinationMarker->pos().x() + DMWIDTH/2) + ", " + QString::number(destinationMarker->pos().y() + DMWIDTH/2));


    int veri=FindArea();
    QTextStream(stdout) << veri << endl;
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

    locationMarker->setRotation(45);
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

        if( destinationMarker->pos().x() + DMWIDTH/2 >= colorAreaPoint.at(i).x)
        {
            if(destinationMarker->pos().y() + DMWIDTH/2 >= colorAreaPoint.at(i).y)
            {
                if(destinationMarker->pos().x() + DMWIDTH/2< ( colorAreaPoint.at(i).width +colorAreaPoint.at(i).x ))
                {
                    if(destinationMarker->pos().y() + DMWIDTH/2< ( colorAreaPoint.at(i).height +colorAreaPoint.at(i).y))
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

    locationMarker->setRotation(input_s.d*-1);
    scene->update();
}

void IcMekan::connectToServer(){


    unsigned short int serverPort = 5005;
    struct sockaddr_in serverAddress;
    struct hostent *hostInfo;
    char buf[LINE_ARRAY_SIZE];
#ifndef __gnu_linux__

    WSADATA AAA;

    //cout << "Enter server host name or IP address: ";
    //cin.get(buf, MAX_LINE, '\n');

    // gethostbyname() takes a host name or ip address in "numbers and
    // dots" notation, and returns a pointer to a hostent structure,
    // which we'll need later.  It's not important for us what this
    // structure is actually composed of.
    WSAStartup(2,&AAA);
#endif
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



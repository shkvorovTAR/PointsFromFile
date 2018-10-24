#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>

using namespace std;
struct Point
{
    float x;
    float y;
    string Name;
};

string PointsLetters [10] = {"A", "B", "C", "D", "E", "F", "G", "H", "J", "E"};
//int pointsCount = 8; //Obozna4enie kolli4estva to4ek v massive (error)

float distance(Point A, Point B); // return distance between point A and B (use Pifagor's Theorem)
float perimeter(Point Array[8]); // return distance perimeter usind function distance 4 times
float area(Point Array[8]); // return area using Gauss's area formula or use Geron formaula for two triangles ABC + ACD

QString printQuad(Point Array[8]);
QString printQuad(Point Array[8])
{
    Point current;
    QString qsTemp;
    QString qsRetVal ="Results: ";
    qsTemp = "\r\nHas perimeter %1 and area %2\r\n";
    qsTemp = qsTemp.arg(perimeter(Array)).arg(area(Array));
    qsRetVal.append(qsTemp);
    return qsRetVal;
   }

float distance(Point A, Point B)
{
    int distance;
    distance = sqrt(pow(B.x-A.x, 2) + pow(B.y-A.y, 2));
    return distance;
}

float perimeter(Point Array[8])
{
    float AB, BC, CD, DA, perimeter;
    AB = distance(Array[0], Array[1]);
    BC = distance(Array[1], Array[2]);
    CD = distance(Array[2], Array[3]);
    DA = distance(Array[0], Array[3]);
    perimeter = AB+BC+CD+DA;
    return perimeter;
}

float area(Point Array[8])
{
    float AB,BC,CD,DA,di,p1,p2,area1,area2,area12;
    AB = distance(Array[0], Array[1]);
    BC = distance(Array[1], Array[2]);
    CD = distance(Array[2], Array[3]);
    DA = distance(Array[0], Array[3]);
    di = sqrt(2) * AB;
    p1 = (AB+BC+di)/2;
    p2 = (CD+DA+di)/2;
    area1 = sqrt(p1*(p1-AB)*(p1-BC)*(p1-di));
    area2 = sqrt(p2*(p2-CD)*(p2-DA)*(p2-di));
    area12 = area1+area2;
    return area12;
}

int main(/*int argc, char *argv[]*/)
{
    //QCoreApplication a(argc, argv);
    qDebug () << "Homework: Perimeter and Area of NGon from file with Points";
    qDebug () <<" ";
    QString message;
    QString qsFileName = "PointsStartFile.txt";
    qsFileName = "PointsStartFile.txt";
    QFile file(qsFileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        message = "Can't open the file %1 for reading\n";
        message = message.arg(qsFileName);
        qDebug() << message;
        return -1;
    }
    Point quadOne[8];
    char buf[2048];
    int readCount;
    QString qsBuf;
    QStringList qslPoint;
    float X,Y;
    int i=0;
    qDebug() << "Points limit is from 3 to 10. You can change it in file 'PointsStartFile.txt'";
    qDebug() << "Also, don't forget to change ArraySize in code!";
    qDebug() << "Points that we found in the file: ";
    qDebug () <<" ";
    while (!file.atEnd())
    {
        readCount = file.readLine(buf, sizeof(buf));
        buf[readCount-1] = 0;
        qsBuf = buf;
        qslPoint = qsBuf.split(';');
        cout << PointsLetters[i] << "_Point:";
        cout << " X: " << qPrintable(qslPoint[0]);
        cout << " Y: " << qPrintable(qslPoint[1])<< endl;
        quadOne[i].x=X;
        quadOne[i].y=Y;
        quadOne[i].Name=PointsLetters[i];
        i++;
    }
    file.close();

    QFile wfile("FinalResults.txt");
       if (wfile.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream writeStream(&wfile);
           writeStream << printQuad(quadOne);
           wfile.close();
           qDebug () <<" ";
           qDebug () <<"To find Area and Perimeter for this points:";
           qDebug () <<"Open 'FinalResults.txt' in build directory!";
           qDebug () <<" ";
   }
    return /*a.exec*/(0);

}

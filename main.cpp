#include "stds.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stds w;
    w.show();
    return a.exec();
}

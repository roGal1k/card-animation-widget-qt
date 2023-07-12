#include "cardanimationwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CardAnimationWidget w;
    w.show();
    return a.exec();
}

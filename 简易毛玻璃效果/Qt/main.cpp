#include "frosted_glass_label.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrostedGlassLabel w;
    w.show();
    return a.exec();
}

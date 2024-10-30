#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    //w.setFixedSize(250,80);//维持窗口默认大小，不可拉伸
    w.setWindowTitle("KCLock");
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);//使用最大化按钮变灰色，不可点击

    w.show();
    return a.exec();
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>

#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QShortcut>
#include <QScreen>
#include <windows.h>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    //组件
    QLabel* lblStandbyPrefix;
    QSpinBox* spnStandby;
    QLabel* lblTimePrefix;
    QSpinBox* spnTime;
    //QCheckBox* chkBootstrap;
    QPushButton *btnLockKeyboardCursor;//锁 按钮

    //布局
    QHBoxLayout *hlayout;//水平布局
    QVBoxLayout *vlayoutMain;//垂直布局(主布局)

    //用户配置数据
    QSettings settings;
    int defaultStandby;
    int defaultTime;

    void showEvent(QShowEvent* event) override;


private slots:
    void lockKeyboardCursor();
    void unLockKeyboardCursor();

};
#endif // WIDGET_H


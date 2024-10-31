#include "widget.h"

Widget::Widget(QWidget *parent):QWidget(parent),settings("GohJophen", "KCLock"){

    // 读取默认值
    defaultStandby = settings.value("standby", 0).toInt();
    defaultTime = settings.value("time", 10).toInt();

    //创建 按钮 对象实例
    lblStandbyPrefix = new QLabel("待机(秒)",this);//"standby(s)"
    spnStandby = new QSpinBox(this);
    lblTimePrefix = new QLabel("定时(秒)",this);//"time(s)"
    spnTime = new QSpinBox(this);
    //chkBootstrap = new QCheckBox("开机自启动",this);//"Bootstrap"
    btnLockKeyboardCursor  =  new QPushButton("锁",this);//"Lock"

    //创建 布局 对象实例
    hlayout = new  QHBoxLayout;//水平布局
    vlayoutMain = new  QVBoxLayout(this);//垂直布局(主布局)

    spnStandby->setRange(0, 86400);  // 设置范围
    spnStandby->setValue(defaultStandby);//设置初始值
    spnTime->setRange(1, 86400);
    spnTime->setValue(defaultTime);

    //设置布局
    hlayout->addWidget(lblStandbyPrefix);
    hlayout->addWidget(spnStandby);
    hlayout->addSpacing(20);
    hlayout->addWidget(lblTimePrefix);
    hlayout->addWidget(spnTime);
    hlayout->addSpacing(80);
    hlayout->addWidget(btnLockKeyboardCursor);
    vlayoutMain->addLayout(hlayout);
    //vlayoutMain->addWidget(chkBootstrap);

    // 设置窗口显示的布局
    setLayout(vlayoutMain);


    // 连接按钮点击事件到锁定/解锁键盘功能
    connect(btnLockKeyboardCursor, &QPushButton::clicked, this, &Widget::lockKeyboardCursor);


}

Widget::~Widget() {}


void Widget::lockKeyboardCursor()
{
    int time = spnTime->value();
    int standby =spnStandby->value();
    // 调用 Windows API，锁定键盘和鼠标输入
    spnStandby->setEnabled(false);
    spnTime->setEnabled(false);
    btnLockKeyboardCursor->setEnabled(false);
    //chkBootstrap->setEnabled(false);
    hide();//窗口隐蔽
    // 等待 standby 秒后锁定输入，time 秒后解锁
    QTimer::singleShot(standby * 1000, this, [=]() {
        BlockInput(TRUE);

        // 创建一个 QTimer 对象，time 秒后调用解锁函数
        QTimer::singleShot(time * 1000, this, &Widget::unLockKeyboardCursor);
    });

}

void Widget::unLockKeyboardCursor()
{
    spnStandby->setEnabled(true);
    spnTime->setEnabled(true);
    btnLockKeyboardCursor->setEnabled(true);
    //chkBootstrap->setEnabled(true);
    showNormal();//窗口正常显现
    // 调用 Windows API，解锁键盘和鼠标输入
    BlockInput(FALSE);
}

void Widget::showEvent(QShowEvent* event) {
    //调用基类 QWidget 的 showEvent 方法;重写事件处理函数（如 showEvent）时，通常需要在自定义实现的开头或结尾调用基类的实现，以确保基类的默认行为能够正常执行
    QWidget::showEvent(event);

    // 获取屏幕的尺寸
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 获取窗口的尺寸
    int windowWidth = this->width();
    int windowHeight = this->height();

    //qDebug() << "Window width:" << windowWidth;
    //qDebug() << "Window height:" << windowHeight;

    // 计算窗口应该显示的位置
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    // 设置窗口的初始位置
    this->move(x, y);

    //this->activateWindow();
}

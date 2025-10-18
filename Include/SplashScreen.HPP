#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include <QSplashScreen>

// TODO: 后期可能增加系统加载提示的动态文字

class SplashScreen : public QSplashScreen{
    Q_OBJECT
    public:
        explicit SplashScreen(const QPixmap& Pixmap, QWidget* Parent = nullptr);
        ~SplashScreen();
};

#endif // SPLASHSCREEN_HPP

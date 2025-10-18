#include "../Include/SplashScreen.HPP"

#include <QApplication>
#include <QThread>

SplashScreen::SplashScreen(const QPixmap& Pixmap, QWidget* Parent) : QSplashScreen(Pixmap){
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setFixedSize(Pixmap.size());
    setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setCursor(Qt::BlankCursor);
}

SplashScreen::~SplashScreen(){}

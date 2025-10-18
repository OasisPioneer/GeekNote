#include "../../Include/WorkSpace/WorkSpace.HPP"

#include <QSettings>
#include <QTimer>
#include <QCloseEvent>
#include <QEvent>
#include <QWindowStateChangeEvent>

WorkSpace::WorkSpace(QSettings* Settings, QWidget* Parent) : Setting(Settings), QWidget(Parent)
{
    this->setWindowTitle(tr("Work Space"));

    // this->resize(800, 600);
    // resize(Settings->value("Window/Size", QSize(800, 600)).toSize());
    // move(Settings->value("Window/Pos", QPoint(100, 100)).toPoint());

    QByteArray geometry = Setting->value("Window/SaveGeometry").toByteArray();
    if (!geometry.isEmpty())
        restoreGeometry(geometry);
    else {
        resize(800, 600);
        move(100, 100);
    }

    IsMaximized  = Setting->value("Window/Maximized", false).toBool();
    IsFullScreen = Setting->value("Window/FullScreen", false).toBool();

    QTimer::singleShot(100, this, [this]() {
        if (IsFullScreen) {
            showFullScreen();
        } else if (IsMaximized) {
            showMaximized();
        } else {
            showNormal();
        }
    });
}

void WorkSpace::closeEvent(QCloseEvent* Event){
    // Setting->setValue("Window/Size", size());
    // Setting->setValue("Window/Pos", pos());

    Setting->setValue("Window/FullScreen", IsFullScreen);
    Setting->setValue("Window/Maximized", IsMaximized);

    if (!IsMaximized && !IsFullScreen)
        Setting->setValue("Window/SaveGeometry", saveGeometry());

    Setting->sync();
    QWidget::closeEvent(Event);
}

void WorkSpace::changeEvent(QEvent* Event)
{
    if (Event->type() == QEvent::WindowStateChange) {
        Qt::WindowStates state = windowState();
        IsFullScreen = (state & Qt::WindowFullScreen);
        IsMaximized  = (state & Qt::WindowMaximized);
    }
    QWidget::changeEvent(Event);
}

WorkSpace::~WorkSpace(){

}

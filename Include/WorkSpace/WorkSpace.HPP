#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include <QWidget>
#include <QSettings>

class WorkSpace : public QWidget{
    Q_OBJECT
    public:
        explicit WorkSpace(QSettings* Settings, QWidget* Parent = nullptr);
        ~WorkSpace();
    protected:
        void closeEvent(QCloseEvent* Event) override;
        void changeEvent(QEvent* Event) override;
    private:
        QSettings* Setting;
        bool IsMaximized = false;
        bool IsFullScreen = false;
};

#endif // WORKSPACE_HPP

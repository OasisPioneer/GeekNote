#ifndef LEFTPANEL_HPP
#define LEFTPANEL_HPP

#include <QWidget>
#include <QSettings>

class QPushButton;
class QLabel;

class LeftPanel : public QWidget{
    Q_OBJECT
    public:
        explicit LeftPanel(QSettings* Setting, QWidget* Parent = nullptr);
    signals:
        void SettingRequest();

    private slots:
        void ShowSettingsMenu();

    private:
        QSettings* Setting_;
        QLabel* NameLabel;
        QLabel* VersionLabel;
        QPushButton* OptionsMenuButton;
};

#endif // LEFTPANEL_HPP

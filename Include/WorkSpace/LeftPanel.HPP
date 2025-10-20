#ifndef LEFTPANEL_HPP
#define LEFTPANEL_HPP

#include <QWidget>
#include <QSettings>

class QPushButton;
class QButtonGroup;
class QLabel;

class LeftPanel : public QWidget{
    Q_OBJECT
    public:
        explicit LeftPanel(QSettings* Setting, QWidget* Parent = nullptr);
    signals:
        void SwitchPages(int Index);
        void SettingRequest();
    public slots:
        void SettingActivitiePage(int Index);
    private slots:
        void ShowSettingsMenu();
    private:
        QSettings* Setting_;
        QLabel* NameLabel;
        QLabel* VersionLabel;

        QButtonGroup* ButtonGroup;
        QPushButton* NoteRepo;
        QPushButton* OptionsMenuButton;
};

#endif // LEFTPANEL_HPP

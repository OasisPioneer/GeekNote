#ifndef RIGHTPANEL_HPP
#define RIGHTPANEL_HPP

#include <QWidget>
#include <QSettings>

class QLineEdit;
class QScrollArea;
class QVBoxLayout;

class RightPanel : public QWidget{
    Q_OBJECT
    public:
        explicit RightPanel(QSettings* Setting, QWidget* Parent = nullptr);
        void LoadProject();
    private:
        QWidget* CreateProjectCard(const QString& Icon, const QString& Name, const QString& Path);
        QSettings* Setting_;
        QVBoxLayout* ScrollLayout;
        QLineEdit* SearchBox;
};

#endif // RIGHTPANEL_HPP

#ifndef NOTEREPO_HPP
#define NOTEREPO_HPP

#include <QWidget>
#include <QSettings>

class QLineEdit;
class QScrollArea;
class QVBoxLayout;

class NoteRepo : public QWidget{
    Q_OBJECT
    public:
        explicit NoteRepo(QSettings* Setting, QWidget* Parent = nullptr);
        void LoadProject();
    private:
        QWidget* CreateProjectCard(const QString& Icon, const QString& Name, const QString& Path);
        bool eventFilter(QObject *obj, QEvent *e) override;

        QSettings* Setting_;
        QVBoxLayout* ScrollLayout;
        QLineEdit* SearchBox;
};

#endif // NOTEREPO_HPP

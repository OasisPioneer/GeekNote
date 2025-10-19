#ifndef APPLICATIONINITIALIZE_HPP
#define APPLICATIONINITIALIZE_HPP

#include <QObject>
#include <QThread>
#include <QSettings>

class ApplicationInitialize : public QObject{
    Q_OBJECT
    public:
        explicit ApplicationInitialize(QObject* Parent = nullptr);
        ~ApplicationInitialize() override;

        void Initialize();
        QSettings* Settings() const { return Setting; }
    signals:
        void Finish();

    private:
        void ReadConfig();

        QSettings* Setting = nullptr;
};

#endif // APPLICATIONINITIALIZE_HPP

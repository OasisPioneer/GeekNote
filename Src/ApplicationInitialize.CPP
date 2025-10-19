#include "../Include/ApplicationInitialize.HPP"

#include <QDebug>

ApplicationInitialize::ApplicationInitialize(QObject* Parent) : QObject(Parent) {}

void ApplicationInitialize::Initialize(){
    QThread* WorkerThread = QThread::create([this]() {
        ReadConfig();
        emit Finish();
    });
    // connect(WorkerThread, &QThread::finished, WorkerThread, &QObject::deleteLater);
    WorkerThread->start();
}

void ApplicationInitialize::ReadConfig(){
    Setting = new QSettings("Styx Studio", "Geek Note");
}

ApplicationInitialize::~ApplicationInitialize() {
    delete Setting;
}

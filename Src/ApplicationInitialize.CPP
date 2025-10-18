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
    for (int i = 0; i < 5; ++i) {
        qDebug() << "加载步骤" << i+1;
        QThread::sleep(1);
    }
}

ApplicationInitialize::~ApplicationInitialize() {}

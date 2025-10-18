#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QScreen>

#include "../Include/SplashScreen.HPP"
#include "../Include/ApplicationInitialize.HPP"
#include "../Include/WorkSpace.HPP"

int main(int argc, char *argv[])
{
    QApplication APP(argc, argv);

    APP.setApplicationName("Geek Note");
    APP.setApplicationVersion("0.1");
    APP.setOrganizationName("Styx Studio");
    APP.setOrganizationDomain("OasisPioneer.COM");
    APP.setWindowIcon(QIcon(":/Image/GeekNote.png"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GeekNote_" + QLocale(locale).name();
        if (translator.load(":/i18n/Language/" + baseName)) {
            APP.installTranslator(&translator);
            break;
        }
    }

    QPixmap Pixmap(":/Image/SplashScreen.png");
    SplashScreen Splash(Pixmap);
    Splash.show();
    APP.processEvents();

    ApplicationInitialize Initialize;

    QObject::connect(&Initialize, &ApplicationInitialize::Finish, &APP, [&Splash, &Initialize]() {
        WorkSpace* WS = new WorkSpace(Initialize.Settings());
        QScreen* Screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = Screen->geometry();
        int X = (screenGeometry.width() - WS->width()) / 2;
        int Y = (screenGeometry.height() - WS->height()) / 2;
        WS->move(X, Y);
        WS->show();
        Splash.finish(WS);
    }, Qt::QueuedConnection);

    Initialize.Initialize();

    return APP.exec();
}

#include "../../Include/Utility/LoadingStyles.HPP"

#include <QFile>
#include <QApplication>

void LoadingStyles(QWidget* Widget, const QString &QssFilePath){
    QFile File(QssFilePath);
    if (!File.open(QFile::ReadOnly | QIODevice::Text)) {
        return;
    }
    QString StyleSheets = QLatin1String(File.readAll());
    Widget->setStyleSheet(StyleSheets);
    File.close();
}

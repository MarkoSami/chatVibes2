#include "welcomepage.h"
#include<QJsonArray>
#include <QApplication>
#include "lib/filesystem_lib.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    do{
    QApplication a(argc, argv);

    QString fontPath = ":/imgs/RozanovaGEO-Demo-SemiBold.otf"; // Replace with your font file path
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont myFont("Tajawal", 12);
    myFont.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    QApplication::setDesktopSettingsAware(true);
    myFont.setHintingPreference(QFont::PreferDefaultHinting);
    QApplication::setFont(myFont);

    WelcomePage welcomeWin ;
    welcomeWin.show();

    // Connect a slot to the QApplication::aboutToQuit signal
    QObject::connect(&a, &QApplication::aboutToQuit, [](){
        fileSystem_lib::saveData();
    });
    currentExitCode = a.exec();
    } while(currentExitCode == profileWindow::EXIT_CODE_REBOOT);

        return currentExitCode;
}

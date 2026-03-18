#include "a8.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "UI.h"
#include "Service.h"
#include "UserService.h"
#include "Coat.h"
#include <crtdbg.h>
#include <QtWidgets/qlabel>
#include <QMessageBox>
int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    Repo repo("repo.txt");
	Service service(repo);
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "File type",
        QString::fromStdString("Would you like to use CSV(YES) or HTML(NO) file"), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        CSVRepo basketRepo("basketRepo");
        UserService userService(repo, basketRepo);
        QTUI ui(service,userService);
        ui.show();
        return a.exec();
    }
    else if (reply == QMessageBox::No) {
       //old one: CSVRepo basketRepo("basketRepo");
        HTMLRepo basketRepo("basketRepo");
        UserService userService(repo, basketRepo);
        QTUI ui(service, userService);
        ui.show();
        return a.exec();
    }
}

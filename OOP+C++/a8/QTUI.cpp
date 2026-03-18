#include "ui.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDesktopServices>
#include "BasketTable.h"
#include <QTableview>
#include <QShortcut>
#include <QKeySequence>


QTUI::QTUI(Service& srv, UserService& usrSrv, QWidget* parent)
    : QMainWindow(parent), serviceRef(srv), userServiceRef(usrSrv) {
    initUI();
}

void QTUI::initUI() {
    auto* tabs = new QTabWidget(this);

    auto* adminWidget = new QWidget();
    auto* userWidget = new QWidget();

    tabs->addTab(adminWidget, "Admin");
    tabs->addTab(userWidget, "User");

    setCentralWidget(tabs);

    // Admin Setup
    auto* adminLayout = new QVBoxLayout(adminWidget);
    auto* adminForm = new QFormLayout();
    auto* adminList = new QListWidget();
    auto* adminAddBtn = new QPushButton("Add Coat");
    auto* adminRemoveBtn = new QPushButton("Remove Coat");
    auto* adminUpdateBtn = new QPushButton("Update Coat");
	auto* adminUndoBtn = new QPushButton("Undo");
	auto* adminRedoBtn = new QPushButton("Redo");

    QLineEdit* sizeEdit = new QLineEdit(), * colorEdit = new QLineEdit(),
        * priceEdit = new QLineEdit(), * quantityEdit = new QLineEdit(),
        * photoEdit = new QLineEdit();

    adminForm->addRow("Size:", sizeEdit);
    adminForm->addRow("Color:", colorEdit);
    adminForm->addRow("Price:", priceEdit);
    adminForm->addRow("Quantity:", quantityEdit);
    adminForm->addRow("Photo:", photoEdit);

    adminLayout->addLayout(adminForm);
    adminLayout->addWidget(adminAddBtn);
    adminLayout->addWidget(adminRemoveBtn);
    adminLayout->addWidget(adminUpdateBtn);
	adminLayout->addWidget(adminUndoBtn);
	adminLayout->addWidget(adminRedoBtn);
    adminLayout->addWidget(adminList);

    auto refreshAdminList = [=]() {
        adminList->clear();
        auto coats = serviceRef.getCoats();
        for (int i = 0; i < coats.size(); ++i) {
            auto c = coats[i];
            adminList->addItem(
                QString::fromStdString(c.getSize() + " | " + c.getColor() + " | " +
                    std::to_string(c.getPrice()) + " | " +
                    std::to_string(c.getQuantity()) + " | " + c.getPhoto()));
        }
        };
    refreshAdminList();
    // Shortcuts for Admin Undo/Redo
    auto* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    connect(undoShortcut, &QShortcut::activated, this, [=]() {
        try {
            serviceRef.Undo();
            refreshAdminList();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    auto* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
    connect(redoShortcut, &QShortcut::activated, this, [=]() {
        try {
            serviceRef.Redo();
            refreshAdminList();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(adminAddBtn, &QPushButton::clicked, this, [=]() {
        try {
			if (priceEdit->text().toInt() == 0 || quantityEdit->text().toInt()==0)
				throw std::runtime_error("Price and quantity must be Integer greater than 0.");
            serviceRef.addCoat(sizeEdit->text().toStdString(), colorEdit->text().toStdString(),
                priceEdit->text().toInt(), quantityEdit->text().toInt(),
                photoEdit->text().toStdString());
            refreshAdminList();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(adminRemoveBtn, &QPushButton::clicked, this, [=]() {
        try {
            serviceRef.removeCoat(sizeEdit->text().toStdString(), photoEdit->text().toStdString());
            refreshAdminList();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(adminUpdateBtn, &QPushButton::clicked, this, [=]() {
        try {
            if (priceEdit->text().toInt() == 0 || quantityEdit->text().toInt() == 0)
                throw std::runtime_error("Price and quantity must be Integer greater than 0.");
            serviceRef.updateCoat(sizeEdit->text().toStdString(), colorEdit->text().toStdString(),
                priceEdit->text().toInt(), quantityEdit->text().toInt(),
                photoEdit->text().toStdString());
            refreshAdminList();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });
	connect(adminUndoBtn, &QPushButton::clicked, this, [=]() {
		try {
			serviceRef.Undo();
			refreshAdminList();
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
		});
	connect(adminRedoBtn, &QPushButton::clicked, this, [=]() {
		try {
			serviceRef.Redo();
			refreshAdminList();
		}
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    // ---------------------- USER TAB ----------------------

    auto* userLayout = new QVBoxLayout(userWidget);
    QLineEdit* sizeSearchEdit = new QLineEdit();
    QPushButton* nextBtn = new QPushButton("Show Next Coat");
    QPushButton* addBtn = new QPushButton("Add to Basket");
    QPushButton* skipBtn = new QPushButton("Don't Add");
    QPushButton* viewBtn = new QPushButton("View Basket");
    QPushButton* undoBtn = new QPushButton("Undo");
    QPushButton* redoBtn = new QPushButton("Redo");
    
    QLabel* currentCoatLabel = new QLabel();
    QLabel* basketPriceLabel = new QLabel("Basket price: 0");
    QListWidget* basketList = new QListWidget();

    userLayout->addWidget(new QLabel("Size:"));
    userLayout->addWidget(sizeSearchEdit);
    userLayout->addWidget(nextBtn);
    userLayout->addWidget(currentCoatLabel);
    userLayout->addWidget(addBtn);
    userLayout->addWidget(skipBtn);
    userLayout->addWidget(viewBtn);
	userLayout->addWidget(undoBtn);
	userLayout->addWidget(redoBtn);
    userLayout->addWidget(basketPriceLabel);
    userLayout->addWidget(basketList);

    Coat* currentCoat = new Coat();

    auto updateCurrentCoatDisplay = [=]() {
        if (currentCoat->getColor() != "")
            currentCoatLabel->setText(QString::fromStdString(currentCoat->getSize() + " | " +
                currentCoat->getColor() + " | " +
                std::to_string(currentCoat->getPrice()) + " | " +
                std::to_string(currentCoat->getQuantity()) + " | " +
                currentCoat->getPhoto()));
        else
            currentCoatLabel->setText("No coat available.");
        };

    connect(nextBtn, &QPushButton::clicked, this, [=]() {
        try {
            std::string size = sizeSearchEdit->text().toStdString();  // Create a local copy
            *currentCoat = userServiceRef.getNextCoat(size, *currentCoat);
            updateCurrentCoatDisplay();
            // Open the coat's photo link in the default browser
            QString photoLink = QString::fromStdString("http://"+currentCoat->getPhoto()+".com");
            QDesktopServices::openUrl(QUrl(photoLink));
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(addBtn, &QPushButton::clicked, this, [=]() {
        if (currentCoat->getColor() == "") {
            QMessageBox::information(this, "Info", "First select a coat.");
            return;
        }
        try {
            userServiceRef.addCoatToBasket(currentCoat->getSize(), currentCoat->getColor(),
                currentCoat->getPrice(), currentCoat->getQuantity(),
                currentCoat->getPhoto());
            basketPriceLabel->setText("Basket price: " + QString::number(userServiceRef.getPrice()));
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());

        }
		});
    connect(skipBtn, &QPushButton::clicked, this, [=]() {
        try {
            std::string size = sizeSearchEdit->text().toStdString();  // Create a local copy
            *currentCoat = userServiceRef.getNextCoat(size, *currentCoat);
            updateCurrentCoatDisplay();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        });

    connect(viewBtn, &QPushButton::clicked, this, [=]() {
        basketList->clear();
        auto coats = userServiceRef.getCoatsFromBasket();
        for (int i = 0; i < coats.size(); ++i) {
            auto c = coats[i];
            basketList->addItem(
                QString::fromStdString(c.getSize() + " | " + c.getColor() + " | " +
                    std::to_string(c.getPrice()) + " | " +
                    std::to_string(c.getQuantity()) + " | " + c.getPhoto()));
        }
        basketPriceLabel->setText("Basket price: " + QString::number(userServiceRef.getPrice()));


        QWidget* tableWindow = new QWidget;
        tableWindow->resize(600, 400);
        QVBoxLayout* layout = new QVBoxLayout(tableWindow);
        QTableView* tableView = new QTableView;
        auto* model = new WatchlistTableModel(userServiceRef.getCoatsFromBasket());
        tableView->setModel(model);
        layout->addWidget(tableView);
        tableWindow->setLayout(layout);
        tableWindow->show();
        });
    QPushButton* openBasketFileBtn = new QPushButton("Open Basket File");
    userLayout->addWidget(openBasketFileBtn);

    connect(openBasketFileBtn, &QPushButton::clicked, this, [=]() {
        QString path = QString::fromStdString(userServiceRef.getBasketRepo().filePath());
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        });
	connect(undoBtn, &QPushButton::clicked, this, [=]() {
		try {
			userServiceRef.Undo();
			basketPriceLabel->setText("Basket price: " + QString::number(userServiceRef.getPrice()));
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
		});
	connect(redoBtn, &QPushButton::clicked, this, [=]() {
		try {
			userServiceRef.Redo();
			basketPriceLabel->setText("Basket price: " + QString::number(userServiceRef.getPrice()));
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
		});

}

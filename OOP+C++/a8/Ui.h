#pragma once
#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "Service.h"
#include "Userservice.h"
#include <iostream>

class QTUI : public QMainWindow {
	Q_OBJECT

private:
	Service& serviceRef;
	UserService& userServiceRef;

	void initUI();


public:
	QTUI(Service& service, UserService& userService, QWidget* parent = nullptr);
};


/*
class UI
{
private:
	Service service;
	UserService userService;
public:
	explicit UI(Service& service, UserService& userService);
	void run();
	void adminUI();
	void userUI();
	~UI();
};
*/
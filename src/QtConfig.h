#pragma once

#include <QWidget>
#include <qmainwindow.h>
#include "ui_QtConfig.h"

class QtConfig : public QMainWindow
{
	Q_OBJECT

public:
	QtConfig(QWidget *parent = Q_NULLPTR);
	~QtConfig();
public slots:
	void saveToConfig();
	void updateLimitLabel(int);
	void cancel();
	void updateLimit(int);
private:
	int backupLimit = 0;
	Ui::QtConfig ui;
};

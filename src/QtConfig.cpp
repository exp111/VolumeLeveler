#include "QtConfig.h"

#include "config.h"
#include "db.h"

QtConfig::QtConfig(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.enableBox->setChecked(config->enabled);
	updateLimitLabel(config->limit);
	ui.limitSlider->setValue(config->limit);
}

QtConfig::~QtConfig()
{
}

void QtConfig::updateLimitLabel(int value)
{
	ui.limitLabel->setText(QString(std::to_string(lin2db(value)).c_str()));
}

void QtConfig::saveToConfig()
{
	config->enabled = ui.enableBox->isChecked();
	config->limit = ui.limitSlider->value();
}
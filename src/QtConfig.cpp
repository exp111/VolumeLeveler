#include "QtConfig.h"

#include "config.h"

QtConfig::QtConfig(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.enableBox->setChecked(config->enabled);
	ui.limitLabel->setText(QString(std::to_string(config->limit).c_str()));
	ui.limitSlider->setValue(config->limit);
}

QtConfig::~QtConfig()
{
}

void QtConfig::updateLimitLabel()
{
	ui.limitLabel->setText(QString(std::to_string(ui.limitSlider->value()).c_str()));
}

void QtConfig::saveToConfig()
{
	config->enabled = ui.enableBox->isChecked();
	config->limit = ui.limitSlider->value();
}
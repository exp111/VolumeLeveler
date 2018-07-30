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
	backupLimit = config->limit;
	ui.actionReasonLine->setText(QString::fromStdString(config->actionReason));
	ui.actionCombo->setCurrentIndex(config->actionOnLevelExceeded);
	ui.banDurationBox->setValue(config->banDuration);
	ui.enableLogBox->setChecked(config->enableLog);
}

QtConfig::~QtConfig()
{
}

void QtConfig::updateLimitLabel(int value)
{
	config->limit = value;
	ui.limitBox->setValue(value);
	//ui.limitBox->setValue(lin2db(value));
	//ui.limitBox->(QString(std::to_string().c_str()));
}

void QtConfig::cancel()
{
	config->limit = backupLimit;
}

void QtConfig::updateLimit(int value)
{
	config->limit = value;
	ui.limitSlider->setValue(value);
}

void QtConfig::saveToConfig()
{
	config->enabled = ui.enableBox->isChecked();
	config->limit = ui.limitSlider->value();
	config->actionOnLevelExceeded = ui.actionCombo->currentIndex();
	config->banDuration = ui.banDurationBox->value();
	config->actionReason = ui.actionReasonLine->text().toStdString();
	config->enableLog = ui.enableLogBox->isChecked();
}
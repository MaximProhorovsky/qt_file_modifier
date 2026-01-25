#include "file_modifier.h"

#include "fm_settings_widget.h"

FileModifier::FileModifier() {
    this->mainWindow = new MainWindow{};
    this->mainWindow->addWidgetToLeftLayout(new SettingsWidget{mainWindow});

}

void FileModifier::show()
{
    this->mainWindow->show();
}

#ifndef SETTINS_H
#define SETTINS_H

#include <QString>

namespace Setting{
    constexpr quint16 THREAD_COUNT = 4;
    const QString BASE_DIR = "C:/";
    const QString BASE_MASK = "*.txt";
    const QChar MASK_DELIMITER = ',';
    constexpr bool OVERWRITE = false;
    constexpr bool WITH_TIMER = false;
    constexpr bool DELETE_SRC_FILES = false;
    constexpr qint32 BASE_TIMEOUT = 5000;
    constexpr qint64 BASE_MODIFIER_VALUE = 0;
}

#endif //SETTINS_H

#pragma once
#include "Colors.h"

// Цветовые палитры и смысловые обозначения цветов
enum Palette: int {
    mainColor = GRAY_ON_BLACK,     // Основной цвет текста
    infoColor = BLACK_ON_LTCYAN,   // Цвет информационных сообщений
    acctColor = RED_ON_WHITE,      // Цвет выделения (акцент)
    hintColor = BLACK_ON_WHITE,    // Цвет подсказок и подсветки
    sumColor  = BLUE_ON_WHITE,     // Цвет суммарных значений
    errColor  = WHITE_ON_RED,      // Цвет ошибок
    resColor  = LTCYAN_ON_BLACK,   // Цвет результатов/подсказок
    arrColor  = LTCYAN_ON_BLACK,   // Цвет массивов/таблиц
    headerColor = WHITE_ON_BLACK   // Цвет заголовков

};

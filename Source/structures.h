#ifndef STRUCTURES_H
#define STRUCTURES_H
// Максимальное колличество точек задания произвольной формы сигнала.
#define MAX_NUM_POINT_FREE_FORM			40


typedef quint32 uint32_t;
typedef qint32 int32_t;
// Тип теста.
typedef enum _STATE_ENUM:unsigned char
{
    STATE_UNKNOWN=0,					// Нет данных.
    TEST_TENSION=33,					// Запущен тест "Растяжение".
    TEST_COMPRESSION=35,				// Запущен тест "Сжатие".
    TEST_CONTROL=36,					// Запущен тест "Поддержание заданного параметра".
    TEST_CYCLING_SINE=37,				// Запущен тест "Циклирование - синусоида".
    TEST_CYCLING_MEANDER=38,			// Запущен тест "Циклирование - меандр".
    TEST_CYCLING_TRIANGLE=39,			// Запущен тест "Циклирование - треугольник".
    TEST_CYCLING_FREE_FORM=40			// Запущен тест "Циклирование - произвольная форма"	.
} STATE_ENUM;
// Тип данных - перечисление типа контролируемого параметра.
typedef enum _TYPE_CONTROL_ENUM:unsigned char
{
    CONTROL_FORCE=0,					// Контролируемая величина - усилие
    CONTROL_MOVING=1,					// Контролируемая величина - перемещение траверсы
    CONTROL_DEFORMATION=2				// Контролируемая величина - деформация
} TYPE_CONTROL_ENUM;
#pragma pack (push, 1)
// Тип данных определяет формат одной записи файла экспорта.
typedef union _FORMAT_EXP_POINT
{
    int32_t ValI32;
    struct
    {
        int32_t IsTimeRecorded:1;			// 1 - Создавать метку времени (мс).
        int32_t IsForceRecorded:1;			// 1 - Создавать запись усилия в 0,1 Н.
        int32_t IsMovingRecorded:1;			// 1 - Создавать запись перемещения в 0,0001 мм.
        int32_t IsDeformationRecorded:1;	// 1 - Создавать запись деформации в 0,0001 мм.
        int32_t IsExtDeformationRecorded:1;	// 1 - Создавать запись деформации (доп. канал) в 0,0001 мм.
        int32_t IsVoltageRecorded:1;		// 1 - Создавать запись точек разности потенциала в 0,0001 мВ.
        int32_t IsTemperatureRecorded:1;	// 1 - Создавать запись точек разности потенциала в 0,0001 мВ.
        // Остальные 25 поля - резерв.
    } Bits;
} FORMAT_EXP_POINT;
// Заголовок файла.
typedef struct _HEADER_EXP_FILE
{
    // Первый блок 16*4=64 байт;
    // Прореживание точек при формировании файла экспорта: 0 - файл не создается; 1 - прорежива-
    // ния исходных данных нет; 2 - пишется каждая вторая точка; 3 - каждая третья точка;......
    int32_t ExpPrescaler;
    // Формат одной записи файла экспорта.
    FORMAT_EXP_POINT FormatExportPoint;
    // Тип теста.
    STATE_ENUM TypeTest;
    unsigned char NuCh[3];
    int32_t NuI32[13];
    // Второй блок - параметры испытания 1024-64 байт.
    union
    {
        unsigned char NuCh[1024-64];
        // Параметры испытаний "Растяжение" и "Сжатие".
        struct _TestTensionCompressionSettings
        {
            // Основные параметры.
            // Предварительная скорость траверсы в 0.001 мм/мин.
            int32_t PrevSpeed;
            // Значение усилия, ниже которого скорость траверсы равна PrevSpeed.
            int32_t ForcePrevSpeed;
            // Рабочая скорость траверсы в 0.001 мм/мин.
            int32_t WorkSpeed;
        } TestTensionCompressionSettings;
        // Параметры испытания "Поддержание заданного параметра".
        struct _TestControlSettings
        {
            // Тип контролируемого параметра.
            TYPE_CONTROL_ENUM TypeControl;
            // Заданное значение.
            int32_t CtrlVal;
            // Время поддержания в секундах.
            uint32_t TimeVal;
        } TestControlSettings;
        // Параметры испытаний "Циклирование - синусоида", "Циклирование - меандр" и "Циклирование
        // - треугольник".
        struct _TestCyclingSettings
        {
            // Тип контролируемого параметра.
            TYPE_CONTROL_ENUM TypeControl;
            // Среднее значение.
            int32_t MeanVal;
            // Переменное значение.
            uint32_t AltVal;
            // База (заданное колличество циклов).
            uint32_t NumberCycles;
            // Период сигнала в мс.
            uint32_t Period;
        } TestCyclingSettings;
        // Параметры испытания  "Циклирование - произвольная форма".
        struct _TestFreeFormSettings
        {
            // Тип контролируемого параметра.
            TYPE_CONTROL_ENUM TypeControl;
            // Колличество точек формы сигнала (1...40)
            unsigned char NumPointsFreeForm;
            // Заданное значение.
            int32_t Val[MAX_NUM_POINT_FREE_FORM];
            // Время выхода в точку, мс
            uint32_t TimeGoTo[MAX_NUM_POINT_FREE_FORM];
            // Время поддержания точки, мс
            uint32_t TimeKeep[MAX_NUM_POINT_FREE_FORM];
            // База (заданное колличество циклов).
            uint32_t NumberCycles;
        } TestFreeFormSettings;
    } TestSettings;
} HEADER_EXP_FILE;
#pragma pack ( pop)

#endif // STRUCTURES_H

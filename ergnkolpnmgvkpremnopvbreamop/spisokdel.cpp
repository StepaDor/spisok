#include <windows.h>
#include <iostream>
using namespace std;

struct datetime
{
    int hour;
    int minute;
    int day;
    int month;
};

struct delo
{
    char name[25];
    int prior;
    char ops[50];
    datetime date;
}*d;

void menu() {
    cout << "\t\t\t\t\t\t  MENU\n";
    cout << "\t\t\t\t\t1 - Ввести новую задачу;\n";
    cout << "\t\t\t\t\t2 - Удалить задачу;\n";
    cout << "\t\t\t\t\t3 - Редактировать задание;\n";
    cout << "\t\t\t\t\t4 - Найти задание;\n";
    cout << "\t\t\t\t\t5 - Вывести на экран задания;\n";
    cout << "\t\t\t\t\t6 - Отсортировать задания;\n";
    cout << "\t\t\t\t\t0 - Выход.\n";
}

void inputDelo(delo& d)
{
    cout << "Введите название задания: ";
    cin.get();
    cin >> d.name;
    cout << "Введите приоритет задания: ";
    cin.get();
    cin >> d.prior;
    cout << "Введите описание задания: ";
    cin.get();
    cin >> d.ops;
    cout << "Введите через пробел день (число) и месяц (число): ";
    cin >> d.date.day >> d.date.month;
    cout << "Введите через пробел час и мунуту: ";
    cin >> d.date.hour >> d.date.minute;
   
}

void deleteDelo(delo* arr, int& size, int index)
{
    if (index >= size)
    {
        cout << "Такого задания не введено" << endl;
        return;
    }
    bool b = false;
    cout << "Вы точно хотите удалить " << arr[index].name << " (1 - да, 0 - нет): ";
    cin >> b;
    if (b)
    {
        arr[index] = arr[size - 1];
        size -= 1;
    }
}

void editDelo(delo* arr, int size, int index)
{
    if (index >= size)
    {
        cout << "Такого задания не введено" << endl;
        return;
    }
    cout << "Введите новое имя: ";
    cin.get(); // пропуск переноса строки
    cin >> arr[index].name;
    cout << "Введите новый приоритет: ";
    cin >> arr[index].prior;
    cout << "Введите новое описание: ";
    cin.get(); // пропуск переноса строки
    cin >> arr[index].ops;
    cout << "Введите через пробел новый день (число) и новый месяц (число): ";
    cin >> arr[index].date.day >> arr[index].date.month;
    cout << "Введите через пробел новый час и новую мунуту: ";
    cin >> arr[index].date.hour >> arr[index].date.minute;
}

int findDeloByName(delo* mas, int size,  char name)
{
    for (int i = 0; i < size; i++)
    {
        if (mas[i].name == &name)
        {
            return i;
        }
    }
    cout << "Такое задание отсутствует!" << endl;
    return -1;
}

int findDeloByPrior(delo* mas, int size, int prior)
{
    for (int i = 0; i < size; i++)
    {
        if (mas[i].prior == prior)
        {
            return i;
        }
    }
    cout << "Такое задание отсутствует!" << endl;
    return -1;
}

int findDeloByOps(delo* mas, int size, const char* ops)
{
    for (int i = 0; i < size; i++)
    {
        if (mas[i].ops == ops)
        {
            return i;
        }
    }
    cout << "Такое задание отсутствует!" << endl;
    return -1;
}

int findDeloByDatetime(delo* mas, int size, datetime date)
{
    for (int i = 0; i < size; i++)
    {
        if (mas[i].date.minute == date.minute &&
            mas[i].date.hour == date.hour &&
            mas[i].date.day == date.day &&
            mas[i].date.month == date.month)
        {
            return i;
        }
    }
    cout << "Такое задание отсутствует!" << endl;
    return -1;
}

void outputDelo(delo* mas, int index)
{
    cout << "Задача номер: " << index << endl;
    cout << "\tНазвание: " << mas[index].name << endl;
    cout << "\tОписание: " << mas[index].ops << endl;
    cout << "\tПриоритет: " << mas[index].prior << endl;
    cout << "\tДата: " << mas[index].date.day << "." << mas[index].date.month << endl;
    cout << "\tВремя: " << mas[index].date.hour << ":" << mas[index].date.minute << endl;
}

void outputDela(delo* mas, int size)
{
    int a = 0;
    cout << "1 - Отобразить задачи на день" << endl;
    cout << "2 - Отобразить задачи на месяц" << endl;

    cin >> a;
    while (cin && (a < 1 || a > 2))
    {
        cout << "Нет такого параметра, попробуйте еще раз" << endl;
        cin >> a;
    }

    datetime dt;
    switch (a)
    {
    case 1:
        cout << "Введите через пробел день (число) и месяц (число): ";
        cin >> dt.day >> dt.month;
        for (int i = 0; i < size; i++)
        {
            if (mas[i].date.day == dt.day && mas[i].date.month == dt.month)
            {
                outputDelo(mas, i);
            }
        }
        break;
    case 2:
        cout << "Введите месяц (число): ";
        cin >> dt.month;
        cout << "Задачи на " << dt.month << "-й месяц:" << endl;
        for (int i = 0; i < size; i++)
        {
            if (mas[i].date.month == dt.month)
            {
                outputDelo(mas, i);
            }
        }
        break;
    default:
        break;
    }
}

void sortDelaByPrior(delo* mas, int size)
{
    for (int i = 0; i + 1 < size; i++)
    {
        for (int j = 0; j + i + 1 < size; j++)
        {
            if (mas[j].prior < mas[j + 1].prior)
            {
                delo t = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = t;
            }
        }
    }
}

void sortDelaByDatetime(delo* mas, int size)
{
    for (int i = 0; i + 1 < size; i++)
    {
        for (int j = 0; j + i + 1 < size; j++)
        {
            if (mas[j].date.month < mas[j + 1].date.month)
            {
                continue;
            }
            bool sameMonth = mas[j].date.month == mas[j + 1].date.month;
            if (
                sameMonth &&
                mas[j].date.day < mas[j + 1].date.day
                )
            {
                continue;
            }
            bool sameDay = mas[j].date.day == mas[j + 1].date.day;
            if (
                sameMonth && sameDay &&
                mas[j].date.hour < mas[j + 1].date.hour
                )
            {
                continue;
            }
            if (
                sameMonth && sameDay &&
                mas[j].date.hour == mas[j + 1].date.hour &&
                mas[j].date.minute <= mas[j + 1].date.minute
                )
            {
                continue;
            }
            delo t = mas[j];
            mas[j] = mas[j + 1];
            mas[j + 1] = t;
        }
    }
}


int main()
{
    system("color B5");
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    delo* mas = new delo[1024]{};

    int size = 0;
    menu();
    int cmd;
    while (cin >> cmd)
    {
        switch (cmd)
        {
        case 1:
            inputDelo(mas[size]);
            size += 1;
            break;
        case 2:
        {
            cout << "Введите номер: ";
            int i;
            cin >> i;
            deleteDelo(mas, size, i);
            break;
        }
        case 3:
        {
            cout << "Введите номер: ";
            int i;
            cin >> i;
            editDelo(mas, size, i);
            break;
        }
        case 4:
        {
            cout << "1 - Поиск по названию" << endl;
            cout << "2 - Поиск по приоритету" << endl;
            cout << "3 - Поиск по описанию" << endl;
            cout << "4 - Поиск по дате и времени" << endl;
            int a;
            cin >> a;
            while (cin && (a < 1 || a > 4))
            {
                cout << "Нет такого параметра, попробуйте еще раз" << endl;
                cin >> a;
            }
            switch (a)
            {
            case 1:
            {
                cout << "Введите название: ";
                char name;
                cin >> name;
                int res = findDeloByName(mas, size, *d->name);
                if (res >= 0)
                {
                    outputDelo(mas, res);
                }
                break;
            }
            case 2:
            {
                cout << "Введите приоритет: ";
                int prior;
                cin >> prior;
                int res = findDeloByPrior(mas, size, prior);
                if (res >= 0)
                {
                    outputDelo(mas, res);
                }
                break;
            }
            case 3:
            {
                cout << "Введите описание: ";
                cin >> *d->ops;
                int res = findDeloByOps(mas, size, d->ops);
                if (res >= 0)
                {
                    outputDelo(mas, res);
                }
                break;
            }
            case 4:
            {
                datetime dt;
                cout << "Введите через пробел день (число) и месяц (число): ";
                cin >> dt.day >> dt.month;
                cout << "Введите через пробел час и мунуту: ";
                cin >> dt.hour >> dt.minute;
                int res = findDeloByDatetime(mas, size, dt);
                if (res >= 0)
                {
                    outputDelo(mas, res);
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case 5:
            outputDela(mas, size);
            break;
        case 6:
        {
            cout << "1 - Сортировка по приоритету" << endl;
            cout << "2 - Сортировка по дате и времени" << endl;
            int a;
            cin >> a;
            while (cin && (a < 1 || a > 2))
            {
                cout << "Нет такого параметра, попробуйте еще раз" << endl;
                cin >> a;
            }
            switch (a)
            {
            case 1:
                sortDelaByPrior(mas, size);
                cout << "Задачи были отсортированы по приоритету" << endl;
                break;
            case 2:
                sortDelaByDatetime(mas, size);
                cout << "Задачи были отсортированы по дате и времени" << endl;
                break;
            default:
                break;
            }
            break;
        }
        case 0:
            if (mas != nullptr)
            {
                delete[] mas;
                mas = nullptr;
            }
            system("color 07");
            return 0;
        default:
            cout << "Нет такой команды, попробуйте еще раз" << endl;
            break;
        }
        cout << endl;
        menu();
    }

    if (mas != nullptr)
    {
        delete[] mas;
        mas = nullptr;
    }
    system("color 07");
    system("pause");
}
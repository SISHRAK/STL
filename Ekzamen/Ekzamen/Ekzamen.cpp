#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#pragma once

using namespace std;

int _stateMenu;
static const int BUFFER_SIZE = 20;
void Menu() {
    cout << "Выберите действие: " << endl
        << "(0) Выход из программы. " << endl
        << "(1) Добавление книг. " << endl
        << "(2) Редактирование книги. " << endl
        << "(3) Сортировка книг. " << endl
        << "(4) Поиск книги." << endl
        << "(5) Просмотр книг." << endl
        << "(6) Очистить файл." << endl
        << "(7) Количество книг." << endl
        << "Ваш выбор: ";
    cin >> _stateMenu;
}

struct Book {
public:
    void PopBook() {
        ofstream f("books.txt", ios::app);
        cout << "Введите название книги " << endl;
        cin >> Title;
        f << Title << " ";
        cout << "Введите ID книги " << endl;
        cin >> Id;
        f << Id << " ";
        cout << "Введите автора книги " << endl;
        cin >> Author;
        f << Author << " ";
        cout << "Введите цену книги " << endl;
        cin >> Price;
        f << Price << endl;
        f << "_________________________" << endl;
        f.close();
    }

    int GetId() {
        return Id;
    }

    char* GetTitle() {
        return Title;
    }

    int GetCount() {
        ifstream f("books.txt", ios::in);
        string str;
        int i = 0;
        while (f) {
            getline(f, str);
            i++;
        }
        f.close();
        return i;
    }

    void WriteBook(ofstream* f) {
        (*f) << Title << ' ' << Id << ' ' << Author << ' ' << Price << "\n_________________________\n";
    }

    void Infomation() {
        cout << Title << '\n' << Id << '\n' << Author << '\n' << Price << '\n';
    }

    void LoadBook(ifstream* f) {
        char c[100];
        char ch;
        (*f).getline(Title, 20, ' ');
        (*f) >> Id >> ch;
        (*f).getline(Author, 20, ' ');
        (*f) >> Price >> ch;
        (*f).getline(c, 100);
    }

private:
    static const int BUFFER_SIZE = 20;
    int Id;
    char Title[BUFFER_SIZE];
    char Author[BUFFER_SIZE];
    float Price;
};

Book* SearchBook(Book* MasBook, int Count, char Title[BUFFER_SIZE]) {
    ofstream f("books.txt", ios::app);
    int first = 0;
    int last = Count - 1;
    while (last != first) {
        int i = (first + last) / 2;
        char* TitleBook = MasBook[i].GetTitle();
        if (strcmp(Title, TitleBook) > 0) {
            first = i + 1;
        }
        else if (strcmp(Title, TitleBook) < 0) {
            last = i - 1;

        }
        else {
            return &(MasBook[i]);
            f.close();
        }
    }
    f.close();
    char* TitleBook = MasBook[last].GetTitle();
    if (strcmp(Title, TitleBook) == 0) {
        return &(MasBook[last]);
        f.close();
    }
    else return nullptr;
}

void Sort(Book* MasBook, int Count) {
    bool b = false;
    while (!b) {
        b = true;
        for (int i = 1; i < Count; i++) {
            char* TitleBook1 = MasBook[i - 1].GetTitle();
            char* TitleBook2 = MasBook[i].GetTitle();
            if (strcmp(TitleBook1, TitleBook2) > 0) {
                b = false;
                Book Book_ = MasBook[i - 1];
                MasBook[i - 1] = MasBook[i];
                MasBook[i] = Book_;
            }
        }
    }
}

void Prosmotr() {
    ifstream f("books.txt");
    while (f) {
        string str;
        f >> str;
        cout << str << endl;
    }
    f.close();
}

void Clear() {
    fstream f("books.txt", ios::out);
    f.clear();
    f.close();
}

int ReadFile(Book** MasBook) {
    ifstream f("books.txt");
    int size = -1;
    while (!f.eof()) {
        size++;
        char c[100];
        f.getline(c, 100);
        f.getline(c, 100);
    }
    f.close();
    (*MasBook) = new Book[size];
    f.open("books.txt");
    for (int i = 0; i < size; i++) {
        (*MasBook)[i].LoadBook(&f);
    }
    f.close();
    return size;
}

void WriteFile(Book* MasBook, int Count) {
    ofstream f("books.txt");
    for (int i = 0; i < Count; i++) {
        MasBook[i].WriteBook(&f);
    }
    f.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
    while (_stateMenu != 0) {
        switch (_stateMenu) {
        case 1: {
            system("cls");
            cout << "Введите данные о книге" << endl;
            Book s;
            s.PopBook();
            system("pause");
            system("cls");
            Menu();
            break;
        }
        case 2: {
            system("cls");
            int Id;
            cout << "Введите ID книги " << endl;
            cin >> Id;
            Book* MasBook = nullptr;
            Book ss;
            int count = ReadFile(&MasBook);

            for (int i = 0; i < count; i++) {
                if (Id == MasBook[i].GetId()) {
                    MasBook[i].PopBook();
                }
            }
            WriteFile(MasBook, count);
            delete[] MasBook;
            system("pause");
            system("cls");
            Menu();
            break;
        }
        case 3: {
            system("cls");
            cout << "Сейчас произойдет сортировка книг по названию " << endl;
            Book* MasBook = nullptr;
            Book s;
            int count;
            count = ReadFile(&MasBook);
            Sort(MasBook, count);
            WriteFile(MasBook, count);
            delete[] MasBook;
            system("pause");
            system("cls");
            Menu();
            break;
        }
        case 4: {
            system("cls");
            char Title[] = "\0";
            Book* MasBook;
            int count;
            count = ReadFile(&MasBook);
            cout << "Введите название книги " << endl;
            cin >> Title;
            Book* pBook = SearchBook(MasBook, count, Title);
            if (pBook == nullptr) cout << "Книга не найдена";
            else(*pBook).Infomation();
            system("pause");
            system("cls");
            delete[] MasBook;
            Menu();
            break;
        }
        case 5: {
            system("cls");
            Prosmotr();
            system("pause");
            system("cls");
            Menu();
            break;
        }
        case 6: {
            system("cls");
            Clear();
            cout << "Файл очищен." << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        }
        case 7: {
            system("cls");
            Book* MasBook;
            Book s;
            cout << "Количество книг - " << s.GetCount() / 2 << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        }
        }
    }
}

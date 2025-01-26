// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(string t, string a) : title(t), author(a) {}
};

class Librery {
private:
    vector<Book> books;

public:
    void addBook(string title, string author) {
        books.emplace_back(title, author);
        cout << "Книга добавлена!" << endl;
    }

    void removeBook(string title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                books.erase(it);
                cout << "Книга удалена!" << endl;
                return;
            }
        }
        cout << "Книга не найдена!" << endl;
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "Нет доступных книг." << endl;
            return;
        }
        cout << "Список книг:" << endl;
        for (const auto& book : books) {
            cout << "Название: " << book.title << ", Автор: " << book.author << endl;
        }
    }
};

int main() {
    Librery lib;
    int choice;
    string title, author;

    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить книгу" << endl;
        cout << "2. Удалить книгу" << endl;
        cout << "3. Просмотреть книги" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите название книги: ";
            cin >> ws;
            getline(cin, title);
            cout << "Введите автора книги: ";
            getline(cin, author);
            lib.addBook(title, author);
            break;
        case 2:
            cout << "Введите название книги для удаления: ";
            cin >> ws;
            getline(cin, title);
            lib.removeBook(title);
            break;
        case 3:
            lib.viewBooks();
            break;
        case 4:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный ввод, попробуйте снова." << endl;
        }
    } while (choice != 4);

    return 0;
}
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

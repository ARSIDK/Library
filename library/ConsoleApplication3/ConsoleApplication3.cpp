#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    bool is_available;

    Book(string t, string a, string g) : title(t), author(a), genre(g), is_available(true) {}
    Book() : is_available(true) {}  // Конструктор по умолчанию
};

class Library {
private:
    vector<Book> books;
    string filename;

    void loadBooks() {
        ifstream file(filename);
        if (file.is_open()) {
            Book book;
            while (getline(file, book.title) && getline(file, book.author) &&
                getline(file, book.genre)) {
                file >> book.is_available;
                file.ignore();  // Игнорировать символ новой строки
                books.push_back(book);
            }
            file.close();
        }
        else {
            cout << "Не удалось открыть файл для чтения.\n";
        }
    }

    void saveBooks() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.title << '\n' << book.author << '\n' << book.genre << '\n'
                    << book.is_available << '\n';
            }
            file.close();
        }
        else {
            cout << "Не удалось открыть файл для записи.\n";
        }
    }

public:
    Library(const string& fname) : filename(fname) {
        loadBooks();
    }

    ~Library() {
        saveBooks();
    }

    void addBook(const string& title, const string& author, const string& genre) {
        books.emplace_back(title, author, genre);
        cout << "Книга \"" << title << "\" добавлена в библиотеку.\n";
    }

    void removeBook(const string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                books.erase(it);
                cout << "Книга \"" << title << "\" удалена из библиотеки.\n";
                return;
            }
        }
        cout << "Книга с названием \"" << title << "\" не найдена.\n";
    }

    void editBook(const string& old_title, const string& new_title, const string& author, const string& genre) {
        for (auto& book : books) {
            if (book.title == old_title) {
                book.title = new_title;
                book.author = author;
                book.genre = genre;
                cout << "Книга \"" << old_title << "\" обновлена.\n";
                return;
            }
        }
        cout << "Книга с названием \"" << old_title << "\" не найдена.\n";
    }

    void searchByGenre(const string& genre) {
        bool found = false;
        for (const auto& book : books) {
            if (book.genre == genre) { // Проверка по жанру
                cout << "Найдена книга: \"" << book.title << "\" автор: " << book.author << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Книги жанра \"" << genre << "\" не найдены.\n";
        }
    }



    void borrowBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                if (book.is_available) {
                    book.is_available = false;
                    cout << "Книга \"" << title << "\" выдана.\n";
                }
                else {
                    cout << "Книга \"" << title << "\" в настоящее время недоступна.\n";
                }
                return;
            }
        }
        cout << "Книга с названием \"" << title << "\" не найдена.\n";
    }

    void returnBook(const string& title) {
        for (auto& book : books) {

            if (book.title == title) {  //функция возврата книг
                if (!book.is_available) {
                    book.is_available = true;
                    cout << "Книга \"" << title << "\" возвращена.\n";
                }
                else {
                    cout << "Книга \"" << title << "\" уже доступна.\n";
                }
                return;
            }
            //Здесь проверяется, совпадает ли название книги с запрашиваемым. 
            // Если книга не была доступна, она становится доступной, и выводится сообщение о её возвращении.
            // Если книга уже доступна, выводится соответствующее сообщение.
        }
        cout << "Книга с названием \"" << title << "\" не найдена.\n";
    }

    void checkAvailability(const string& title) {  //функция проверки доступности книг
        for (const auto& book : books) {
            if (book.title == title) {
                if (book.is_available) {
                    cout << "Книга \"" << title << "\" доступна.\n";
                }
                else {
                    cout << "Книга \"" << title << "\" недоступна.\n";
                }
                return;
            }
        }
        cout << "Книга с названием \"" << title << "\" не найдена.\n";
    }
    //Эта функция перебирает книги в библиотеке и проверяет, доступна ли указанная книга.
    // Если книга не найдена, выводится соответствующее сообщение.
};

int main() {
    setlocale(LC_ALL, "ru");
    Library library("books.txt");

    library.addBook("1984", "Джордж Оруэлл", "Дистопия");
    library.addBook("Мастер и Маргарита", "Михаил Булгаков", "Фантастика");

    library.searchByGenre("Джордж Оруэлл");
    library.checkAvailability("1984");
    library.borrowBook("1984");
    library.checkAvailability("1984");
    library.returnBook("1984");
    library.checkAvailability("1984");

    library.removeBook("1984");
    library.checkAvailability("1984");

    return 0;
}

//В функции main создается объект библиотеки и добавляются книги. 
// Далее происходит ряд действий: поиск книг по автору, проверка доступности, заём и возврат книги, а также её удаление.


//это объяснение к началу кода, половина кода уже сверху рядом и под кодом.


// обзор кода: структура book: хранит информацию о книгах. имеет два конструктора: один для инициализации значений, а второй 
//для создания объекта по умолчанию. 
//класс librari: содержит вектор книг и название файла для хранения и загрузки данных. 
//имеет приватные методы для загрузки и сохранения книг. ( loadBooks и saveBooks)

//методы либрари: 
// - addBook: добавляет новую книгу в библиотеку.
// -removeBook: удаляет книгу по названию.
// - editBook : изменяет данные о книге.
// - searchByAuthor : ищет книги по автору.
// - searchByGenre : ищет книги по жанру.
// - borrowBook : выдает книгу читателю, обновляя статус доступности.
// - returnBook : возвращает книгу в библиотеку(метод не завершен в вашем коде).

// обработка файлов: класс загружает книги из текст. файла при инициализации и сохраняет измениния 
//в файл при уничтожении объекта. это позволяет сохранять данные между запусками прогруммы.

// малое примечание.
//- Обработка ошибок реализована, что позволяет избежать сбоев при работе с файлами.
//- Рекомендуется добавить функции для отображения всех книг и улучшить взаимодействие с пользователем(например, через интерфейс).



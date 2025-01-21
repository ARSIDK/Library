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

    void searchByAuthor(const string& author) {
        cout << "Поиск книг по автору \"" << author << "\":\n";
        for (const auto& book : books) {
            if (book.author == author) {
                cout << " - " << book.title << " (Жанр: " << book.genre << ")\n";
            }
        }
    }

    void searchByGenre(const string& genre) {
        cout << "Поиск книг по жанру \"" << genre << "\":\n";
        for (const auto& book : books) {
            if (book.genre == genre) {
                cout << " - " << book.title << " (Автор: " << book.author << ")\n";
            }
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

            if (book.title == title) {
                if (!book.is_available) {
                    book.is_available = true;
                    cout << "Книга \"" << title << "\" возвращена.\n";
                }
                else {
                    cout << "Книга \"" << title << "\" уже доступна.\n";
                }
                return;
            }
        }
        cout << "Книга с названием \"" << title << "\" не найдена.\n";
    }

    void checkAvailability(const string& title) {
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
};

int main() {
    setlocale(LC_ALL, "ru");
    Library library("books.txt");

    library.addBook("1984", "Джордж Оруэлл", "Дистопия");
    library.addBook("Мастер и Маргарита", "Михаил Булгаков", "Фантастика");

    library.searchByAuthor("Джордж Оруэлл");
    library.checkAvailability("1984");
    library.borrowBook("1984");
    library.checkAvailability("1984");
    library.returnBook("1984");
    library.checkAvailability("1984");

    library.removeBook("1984");
    library.checkAvailability("1984");

    return 0;
}


using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

class Book {
private:
    std::string title;   // Название книги
    std::string author;  // Автор книги
    int year;            // Год выпуска
    std::string url;     // URL на книгу
    std::string publisher; // Издательство
    int pages;           // Количество страниц

    // Вектор для хранения массива книг
    static std::vector<Book> books;

public:
    // Конструктор по умолчанию и с параметрами
    Book(std::string title = "", std::string author = "", int year = 0, std::string url = "", std::string publisher = "", int pages = 0)
        : title(title), author(author), year(year), url(url), publisher(publisher), pages(pages) {}

    // Чтение данных о книге
    void read() {
        std::cout << "Введите название книги: ";
        std::cin.ignore();
        std::getline(std::cin, title);

        std::cout << "Введите автора (Фамилия И.О.): ";
        std::getline(std::cin, author);

        std::cout << "Введите год издания: ";
        while (!(std::cin >> year) || year < 0) {
            std::cout << "Неверный год. Введите снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        std::cout << "Введите издательство: ";
        std::getline(std::cin, publisher);

        std::cout << "Введите количество страниц: ";
        while (!(std::cin >> pages) || pages <= 0) {
            std::cout << "Неверное количество страниц. Введите снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        std::cout << "Введите URL на книгу (если есть): ";
        std::getline(std::cin, url);
    }

    // Метод для отображения информации о книге
    void display() const {
        std::cout << "Название: " << title << "\n"
                  << "Автор: " << author << "\n"
                  << "Год: " << year << "\n"
                  << "Издательство: " << publisher << "\n"
                  << "Страниц: " << pages << "\n"
                  << "URL: " << url << "\n";
    }

    // Генерация библиографической записи
    std::string generateBibliography() const {
        std::ostringstream oss;
        oss << author << " " << title << ". – "
            << publisher << ", " << year << ". – "
            << pages << " с.";
        return oss.str();
    }

    // Добавление книги
    static void addBook() {
        Book newBook;
        newBook.read();
        books.push_back(newBook);
        saveBooksToFile();
    }

    // Удаление книги
    static void removeBook(size_t index) {
        if (index < books.size()) {
            books.erase(books.begin() + index);
            std::cout << "Книга успешно удалена.\n";
            saveBooksToFile();
        } else {
            std::cout << "Неверный индекс. Книга не удалена.\n";
        }
    }

    // Отображение библиографического списка
    static void displayBibliography() {
        if (books.empty()) {
            std::cout << "Список литературы пуст.\n";
            return;
        }
        std::cout << "\nСписок литературы (по ГОСТ):\n";
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i + 1 << ". " << books[i].generateBibliography() << "\n";
        }
    }

    // Сохранение книг
    static void saveBooksToFile() {
        std::ofstream file("books_database.txt", std::ios::trunc);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.title << "\n"
                     << book.author << "\n"
                     << book.year << "\n"
                     << book.publisher << "\n"
                     << book.pages << "\n"
                     << book.url << "\n";
            }
        }
        file.close();
    }

    // Загрузка книг
    static void loadBooksFromFile() {
        books.clear();
        std::ifstream file("books_database.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                Book book;
                std::getline(file, book.title);
                std::getline(file, book.author);
                file >> book.year;
                file.ignore();
                std::getline(file, book.publisher);
                file >> book.pages;
                file.ignore();
                std::getline(file, book.url);
                if (!file.fail()) {
                    books.push_back(book);
                }
            }
        }
        file.close();
    }

    // Меню для взаимодействия с пользователем
    static void menu() {
        loadBooksFromFile(); // Загрузка книг из базы данных
        int choice = 0;
        while (choice != 3) {
            std::cout << "\nМеню:\n"
                      << "1. Добавить книгу\n"
                      << "2. Отобразить список литературы\n"
                      << "3. Выход\n"
                      << "Введите ваш выбор: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                addBook();
                saveBooksToFile();
                break;
            case 2:
                displayBibliography();
                break;
            case 3:
                std::cout << "Завершение работы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }
    }
};

// Инициализация статической переменной
std::vector<Book> Book::books;

int main()
{
    Book library; // Объект для работы с книгами
    library.menu(); // Запуск интерфейса пользователя

    return 0;
}
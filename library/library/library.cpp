#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
	string title;
	string author;
	int year;
	string isbn;
	bool isAvailable;
public:
	Book(string _title, string _author, int _year, string _isbn, bool _isAvailable) {
		title = _title;
		author = _author;
		year = _year;
		isbn = _isbn;
		isAvailable = _isAvailable;
	}

	void set_yaer(int year) {this->year = year;}
	void set_isAvailable(bool isAvailable) {this->isAvailable = isAvailable;}


	string get_title() const { return title; }
	string get_author() const { return author; }
	int get_year() const { return year; }
	string get_isbn() const { return isbn; }
	bool get_isAvailable() const { return isAvailable; }

	void displayInfo() {
		cout << get_title() << endl;
		cout << get_author() << endl;
		cout << get_year() << endl;
		cout << get_isbn() << endl;
		cout << get_isAvailable() << endl;
	}
};


class Library {
private:
	vector<Book> catalog;
public:
	Library() {}

	void addBook(const Book& book) {
		catalog.push_back(book);
	}
	void removeBook(const string& isbn) {
		for (int i = 0; i < catalog.size(); i++) {
			if (catalog[i].get_isbn() == isbn) {
				catalog.erase(catalog.begin() + i);
				return;
			}
		}
	}

	Book* findBookByISBN(const string& isbn) {
		for (int i = 0; i < catalog.size(); i++) {
			if (catalog[i].get_isbn() == isbn)
				return &catalog[i];	
		}
		return nullptr;
	}

	void listAllBooks() {
		for (int i = 0; i < catalog.size(); i++) {
			cout << catalog[i].get_title() << endl;
		}
	}

	bool borrowBook(const string& isbn) {
		for (int i = 0; i < catalog.size(); i++) {
			if (catalog[i].get_isbn() == isbn) {
				if (catalog[i].get_isAvailable() == true) {
					catalog[i].set_isAvailable(false);
					return true;
				}
			}
		}
		return false;
	}

	bool returnBook(const string& isbn) {
		for (int i = 0; i < catalog.size(); i++) {
			if (catalog[i].get_isbn() == isbn) {
				catalog[i].set_isAvailable(true);
				return true;
			}
		}
		return false;
	}

};

int main() {
	Library lib;

	lib.addBook(Book("1984", "Orwell", 1949, "111", true));
	lib.addBook(Book("Brave New World", "Huxley", 1932, "222", true));

	lib.listAllBooks();

	cout << lib.borrowBook("111") << endl;
	cout << lib.borrowBook("111") << endl;

	cout << lib.returnBook("111") << endl;
	cout << lib.borrowBook("111") << endl;

	return 0;
}
#include <iostream>
#include <string.h>

using namespace std;

namespace Space { //stworzenie pierwszej przestrzeni nazw

  namespace NestedSpace { //stworzenie zagniezdzone przestrzeni nazw
    class Library { 
    private:  
      string name;
      char location_city[25];
    public:
      Library(string name, const char* location) {
        cout << "Name of the library: " << name << endl;
        strcpy(location_city, location);
        cout << "Location: " << location_city << endl;
      }
      struct Book { //struktura "Ksiazka", ktora jest zagniezdzona w klasie "Biblioteka"
        string title;
        string author;
        int pages;
        static int counter;

        Book() { //konstruktor domyslny
          title = "Book";
          author = "Author";
          pages = 99;
          counter++;
        }
        Book(string t, string a, int p) { //konstruktor parametryzujacy
          title = t;
          author = a;
          pages = p;
          counter++;
          cout << "Title: " << title << "; author: " << author << "; amount of pages: " << pages << endl;
        }
      };
      void pages(Library::Book* books, int counter) {
        int temp = 0;
        int biggest = 0;
        for(int i = 0; i < counter; i++) {
          if (books[i].pages > biggest) {
            temp = i;
          }
        }
        cout << books[temp].title << " by " << books[temp].author << " has the biggest amount of pages.";
      }
    };
  }
  class Reader { //utworzenie klasy Czytelnik w pierwszej przestrzeni nazw
  private: 
    string first_name;
    string last_name;
    int amount_of_borrowed_books;
    NestedSpace::Library::Book** borrowed_books;
  public: 
    int get_amount() {
      return amount_of_borrowed_books;
    }
    NestedSpace::Library::Book** get_books() {
      return borrowed_books;
    }    
    Reader(string f, string l, int b) {
      first_name = f;
      last_name = l;
      amount_of_borrowed_books = b;
      cout << "First name: " << first_name << endl << "Last name: " << last_name << endl << "Borrowed books: " << amount_of_borrowed_books << endl;
      borrowed_books = new NestedSpace::Library::Book*[amount_of_borrowed_books];
    }
    void borrow(NestedSpace::Library::Book& b1, NestedSpace::Library::Book& b2, NestedSpace::Library::Book& b3) {
      borrowed_books[0] = &b1;
      borrowed_books[1] = &b2;
      borrowed_books[2] = &b3;
    }
    ~Reader(){
      delete[] borrowed_books;
    }
  };
  void showBorrowedBooks(Reader& r) {
    for(int i = 0; i < r.get_amount(); i++) {
      cout << "Title: " << r.get_books()[i]->title << "; author: " << r.get_books()[i]->author << "; amount of pages: " << r.get_books()[i]->pages << endl;      
    }
  }
}

typedef Space::NestedSpace::Library Lib;

int Lib::Book::counter = 0;

int main() {
  Lib library("United Library", "New York"); cout << endl;

  Lib::Book books[4] = {Lib::Book("First Book", "American Author", 7), Lib::Book("Second Book", "English Author", 20), Lib::Book("Third Book", "Polish Author", 50), Lib::Book("Fourth Book", "French Author", 390)}; cout << endl;

  Space::Reader reader("Johnny", "Bravo", 3); cout << endl;

  reader.borrow(books[0], books[2], books[3]);

  Space::showBorrowedBooks(reader); cout << endl;

  library.pages(books, Lib::Book::counter); cout << endl;

  cout << "Counter: " << Lib::Book::counter;

  return 0;
}
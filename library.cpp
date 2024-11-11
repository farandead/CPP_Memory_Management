#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<cstring>
// Make a Book Class with id , name , author , price , year of publication
// Make a library class with a list of books , capacity of library , number of books, and functions to add book , delete book , search book by name

class Book{
    public:
        int id;
        char *title;
        char *author;
        float price;
        int year;

        Book(int id, const char *title, const char *author, float price, int year):id(id),price(price),year(year){
            this->title = new char[strlen(title)+1];
            std::strcpy(this->title,title);
            this->author = new char[strlen(author)+1];
            std::strcpy(this->author,author);
        }
	
        int getId() const {
            return id;
        }
        
        const char *getTitle()const{
            return title;
        }
        const char *getAuthor() const{
            return author;
        }
        int getYear() const{
            return year;
        }
        float getPrice() const{
            return price;
        }
        
        ~Book(){
            delete[] title;
            delete[] author;
        };
};

class Library{
	public:
		Book** books;
		int capacity;
		int count;
		Library(int capacity): capacity(capacity),count(0){
			books = new Book*[capacity];
		};
		~Library(){
			for(int i = 0;i < count;i++){
				delete books[i];
			}
			delete [] books;
		};
		
		bool addBook(const int id, const char *title,const char*author,float price, int year){
			if( count == capacity) resize();
			books[count++] = new Book(id,title,author,price,year);

            return true;
		};
		bool deleteBook(int id){
			for(int i = 0;i < count;i++){
				if (books[i]->getId() == id){
					delete books[i];
					books[i] = books[--count];
					return true;
				}
			};

            return false;
			
		};
		void displayBooks() const{
			for(int i = 0;i <count; i++){
				std::cout<<"ID: "<<books[i]->getId()<<"\n"<<books[i]->getTitle()<<"\n"<<books[i]->getAuthor()<<"\n"<<books[i]->getPrice()<<"\n"<<books[i]->getYear()<<"\n";
			}
			
		}
		Book* searchBookByName(const char* targetname){
			for(int i = 0;i < count; i++){
				if(std::strcmp(books[i]->getTitle() , targetname) == 0){
					return books[i];
				}
			}
			return nullptr;
		
		};
		private:
			void resize(void){
				capacity*=2;
				Book** newBooks = new Book*[capacity];
				for(int i = 0; i < count;i++){
					newBooks[i] = books[i];
				}
				delete [] books;
				books = newBooks;
			};
		
		
};

int main() {
    Library myLibrary(2);

    myLibrary.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald", 10.99, 1925);
    myLibrary.addBook(2, "To Kill a Mockingbird", "Harper Lee", 7.99, 1960);
    myLibrary.addBook(3, "1984", "George Orwell", 8.99, 1949); 

    std::cout << "All books in library:" << std::endl;
    myLibrary.displayBooks();

    const char* searchTitle = "1984";
    Book* foundBook = myLibrary.searchBookByName(searchTitle);
    if (foundBook) {
        std::cout << "\nBook found:" << std::endl;
        std::cout << "ID: " << foundBook->getId() << "\n"
                  << "Title: " << foundBook->getTitle() << "\n"
                  << "Author: " << foundBook->getAuthor() << "\n"
                  << "Price: " << foundBook->getPrice() << "\n"
                  << "Year: " << foundBook->getYear() << "\n";
    } else {
        std::cout << "\nBook not found" << std::endl;
    }

    int deleteId = 2;
    bool isDeleted = myLibrary.deleteBook(deleteId);
    if (isDeleted) {
        std::cout << "\nBook with ID " << deleteId << " has been deleted." << std::endl;
    } else {
        std::cout << "\nBook with ID " << deleteId << " not found for deletion." << std::endl;
    }
    std::cout << "\nAll books in library after deletion:" << std::endl;
    myLibrary.displayBooks();

    return 0;
}

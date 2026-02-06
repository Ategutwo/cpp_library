#include <ctime>
#include <vector>
#include <iostream>
using namespace std;
class Book;
class User;
class BookCopy;
class Library;

class Book{
private:
    string title;
    string author;
    string ISBN;
    
    Book(string t, string a, string i) : title(t), author(a), ISBN(i) {}
    
public:
    static Book createBook(string t, string a, string i){
        return Book(t, a, i);
    }
    
    void displayInfo() {    
        std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN  << std::endl;
    }
    const string& getTitle()const{
        return title;
    };
    const string& getISBN()const{
        return ISBN;
    }
    const string& getAuthor()const{
        return author;
    }
    
};

class User{
private:
    string name;
    int userID;
    string email;
    User(string name,int id,string email):name(name),userID(id),email(email){};
    
public:
    static User createUser(string firstName,string lastName,int id,string email){
        return User(firstName +" "+ lastName,id,email);
    }
    
    const string& getName()const{
        return name;
    }
    int getUserID()const{
        return userID;
    }
};

class BookCopy{
private:
    Book *book;
    User *issuedTo;
    bool isAvailable;
    time_t dateIssued;
    time_t expectedReturnDate;
    
    BookCopy(Book *book):book(book), issuedTo(NULL), isAvailable(true), dateIssued(0), expectedReturnDate(0){}
    
public:
    static BookCopy createCopy(Book *book){
        return BookCopy(book);
    }
    User *getCurrentUser(){
        return issuedTo;
    }
    
    void returnBook(){
        issuedTo = NULL;
        isAvailable = true;
        dateIssued = 0;
        expectedReturnDate = 0;
    }
    
    void setBookReturnDate(time_t returnDate){
        expectedReturnDate = returnDate;
    }
    
    void issueToUser(User *user){
        issuedTo = user;
        dateIssued = time(NULL);
        isAvailable = false;
    }
    
    bool getIsAvailable()const{
        return isAvailable;
    }
    
    Book* getBook()const{
        return book;
    }
    
    bool isOverdue(){
        if(!isAvailable && expectedReturnDate > 0){
            time_t currentDate = time(NULL);
            if(currentDate > expectedReturnDate){
                return true;
            }
        }
        return false;
    }
};

class Library {
private:
    vector<Book> books;
    vector<BookCopy> copies;
    vector<User> members;
    
public:
    void listBooks() {
        std::cout << "Listing all books in the library." << std::endl;
        for(int i = 0; i < books.size(); i++){
            cout << i << ". " << books[i].getTitle() << std::endl;
        }
    }
    void addBookCopies(const string& bookName,int quantity){
       Book* book = searchBook(bookName);
       if(book != nullptr){
        for(int i = 0;i<=quantity;i++){
            copies.push_back(BookCopy::createCopy(book));
        }
       }
       else{
        cout<<"Cannot add book copies. Does not exist in library. Please add book first";
       }

    }
    void addBook(Book book) {
        bool bookExists = false;
        for(int i = 0; i < books.size(); i++){
            if(books[i].getTitle() == book.getTitle() 
            && (books[i].getAuthor() == book.getAuthor())
            && (books[i].getISBN() == book.getISBN())){
                bookExists = true;
            }
        }
        if(!bookExists){
            books.push_back(book);
            //Add atleast one book copy
            copies.push_back(BookCopy::createCopy(&books[books.size()-1]));
            cout << "Adding book: " << book.getTitle() << endl;
        }
        else{
            cout << "Adding book: " << book.getTitle() << " failed. Book already exists" << endl;
        }
    }
    
    void removeBook(const string& bookName) {
        int bookIndex = -1;
        for(int i = 0; i < books.size(); i++){
            if(books[i].getTitle() == bookName){
                bookIndex = i;
                break;
            }
        }
        if(bookIndex >= 0){
            books.erase(books.begin() + bookIndex);
            cout << "Removing book: " << bookName << endl;
        }
        else{
            cout << "Book not found: " << bookName << endl;
        }
    }
    
    Book* searchBook(const string& bookName) {
        std::cout << "Searching for book: " << bookName << std::endl;
        bool found = false;
        int bookIndex = -1;
        for(int i = 0; i < books.size(); i++){
            if(books[i].getTitle() == bookName){
                books[i].displayInfo();
                found = true;
            }
        }
        if(!found && bookIndex>=0){
            cout << "Book not found." << endl;
            return &books[bookIndex];
        }
        return nullptr;
    }
    
    void issueBook(const std::string& bookName) {
        std::cout << "Isuing book: " << bookName << std::endl;
    }
    
    void returnBook(const std::string& bookName) {
        std::cout << "Returning book: " << bookName << std::endl;
    }
    
    void displayMembers() {
        std::cout << "Dispaying all library members." << std::endl;
        for(int i = 0; i < members.size(); i++){
            cout << i << ". " << members[i].getName() << " (ID: " << members[i].getUserID() << ")" << endl;
        }
    }
    
    void addMember(User user) {
        members.push_back(user);
        std::cout << "Adding member: " << user.getName() << std::endl;
    }
    
    void removeMember(const std::string& memberName) {
        int memberIndex = -1;
        for(int i = 0; i < members.size(); i++){
            if(members[i].getName() == memberName){
                memberIndex = i;
                break;
            }
        }
        if(memberIndex >= 0){
            members.erase(members.begin() + memberIndex);
            cout << "Removing member: " << memberName << endl;
        }
        else{
            cout << "Member not found: " << memberName << endl;
        }
    }
    
    bool isBookAvailable(const std::string& bookName) {
        std::cout << "Checking availability for book: " << bookName << std::endl;
        for(int i = 0; i < copies.size(); i++){
            if(copies[i].getBook()->getTitle() == bookName && copies[i].getIsAvailable()){
                return true;
            }
        }
        return false;
    }
    
    bool isMemberValid(const std::string& memberName) {
        std::cout << "Checking validity for member: " << memberName << std::endl;
        for(int i = 0; i < members.size(); i++){
            if(members[i].getName() == memberName){
                return true;
            }
        }
        return false;
    }
    
    bool hasOverdueBooks(const std::string& memberName) {
        if(isMemberValid(memberName)){
            for(int i =0;i<copies.size();i++){
                if(copies[i].getCurrentUser()->getName() == memberName && copies[i].isOverdue()){
                    return true;
                }
            }
        }
        return false;
    }
};

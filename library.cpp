#include <iostream>
#include <vector>
#include <ctime>
#include <map>
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
    
    void searchBook(const std::string& bookName) {
        std::cout << "Searching for book: " << bookName << std::endl;
        bool found = false;
        for(int i = 0; i < books.size(); i++){
            if(books[i].getTitle() == bookName){
                books[i].displayInfo();
                found = true;
            }
        }
        if(!found){
            cout << "Book not found." << endl;
        }
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
        std::cout << "Checking overdue books for member: " << memberName << std::endl;
        return false;
    }
};

void displayMessage() {
    std::cout << "Welcome to Alvins Library!" << std::endl;
}

int main()
{
    displayMessage();
    Library lib = Library();
    
    cout << "\n=== TEST CASE 1: Adding Books ===" << endl;
    Book book1 = Book::createBook("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565");
    Book book2 = Book::createBook("1984", "George Orwell", "978-0451524935");
    Book book3 = Book::createBook("To Kill a Mockingbird", "Harper Lee", "978-0061120084");
    Book book4 = Book::createBook("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565"); // Duplicate
    
    lib.addBook(book1);
    lib.addBook(book2);
    lib.addBook(book3);
    lib.addBook(book4); // Should fail - duplicate
    
    cout << "\n=== TEST CASE 2: Listing Books ===" << endl;
    lib.listBooks();
    
    cout << "\n=== TEST CASE 3: Searching Books ===" << endl;
    lib.searchBook("1984"); // Should find
    lib.searchBook("Harry Potter"); // Should not find
    
    cout << "\n=== TEST CASE 4: Adding Members ===" << endl;
    User user1 = User::createUser("John", "Doe", 1001, "john.doe@university.edu");
    User user2 = User::createUser("Jane", "Smith", 1002, "jane.smith@university.edu");
    User user3 = User::createUser("Bob", "Johnson", 1003, "bob.johnson@university.edu");
    
    lib.addMember(user1);
    lib.addMember(user2);
    lib.addMember(user3);
    
    cout << "\n=== TEST CASE 5: Displaying Members ===" << endl;
    lib.displayMembers();
    
    cout << "\n=== TEST CASE 6: Checking Member Validity ===" << endl;
    bool valid1 = lib.isMemberValid("John Doe"); // Should be valid
    bool valid2 = lib.isMemberValid("Alice Wonder"); // Should be invalid
    cout << "John Doe valid: " << (valid1 ? "Yes" : "No") << endl;
    cout << "Alice Wonder valid: " << (valid2 ? "Yes" : "No") << endl;
    
    cout << "\n=== TEST CASE 7: Removing a Book ===" << endl;
    lib.removeBook("1984"); // Should succeed
    lib.removeBook("Nonexistent Book"); // Should fail
    lib.listBooks();
    
    cout << "\n=== TEST CASE 8: Removing a Member ===" << endl;
    lib.removeMember("Bob Johnson"); // Should succeed
    lib.removeMember("Nonexistent Member"); // Should fail
    lib.displayMembers();
    
    cout << "\n=== TEST CASE 9: Book Availability ===" << endl;
    bool available1 = lib.isBookAvailable("The Great Gatsby");
    cout << "The Great Gatsby available: " << (available1 ? "Yes" : "No") << endl;
    
    cout << "\n=== TEST CASE 10: Edge Case - Empty Library Operations ===" << endl;
    Library emptyLib = Library();
    emptyLib.listBooks(); // Empty list
    emptyLib.searchBook("Any Book"); // Nothing to find
    emptyLib.displayMembers(); // No members
    
    cout << "\n=== TEST CASE 11: Edge Case - Special Characters in Names ===" << endl;
    Book book5 = Book::createBook("Alice's Adventures", "Lewis Carroll", "978-1234567890");
    User user4 = User::createUser("Mary-Jane", "O'Connor", 1004, "mj.oconnor@uni.edu");
    lib.addBook(book5);
    lib.addMember(user4);
    lib.searchBook("Alice's Adventures");
    
    cout << "\n=== TEST CASE 12: Edge Case - Long Names ===" << endl;
    Book book6 = Book::createBook("A Very Long Title That Tests The System's Ability To Handle Extended Book Names", 
                                   "Author With Multiple Middle Names", "978-9876543210");
    lib.addBook(book6);
    lib.listBooks();
    
    cout << "\n=== TEST CASE 13: Edge Case - Case Sensitivity ===" << endl;
    lib.searchBook("the great gatsby"); // Different case - won't find (case sensitive)
    lib.searchBook("The Great Gatsby"); // Exact match - will find
    
    cout << "\n=== TEST CASE 14: BookCopy Operations ===" << endl;
    BookCopy copy1 = BookCopy::createCopy(&book1);
    cout << "Book copy created for: " << book1.getTitle() << endl;
    cout << "Is available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
    
    copy1.issueToUser(&user1);
    cout << "After issuing to user:" << endl;
    cout << "Is available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
    
    time_t returnDate = time(NULL) + (14 * 24 * 60 * 60); // 14 days from now
    copy1.setBookReturnDate(returnDate);
    cout << "Is overdue: " << (copy1.isOverdue() ? "Yes" : "No") << endl;
    
    copy1.returnBook();
    cout << "After returning book:" << endl;
    cout << "Is available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
    
    cout << "\n=== TEST CASE 15: Overdue Book Simulation ===" << endl;
    BookCopy copy2 = BookCopy::createCopy(&book2);
    copy2.issueToUser(&user2);
    time_t pastDate = time(NULL) - (7 * 24 * 60 * 60); // 7 days ago
    copy2.setBookReturnDate(pastDate);
    cout << "Book issued with past return date" << endl;
    cout << "Is overdue: " << (copy2.isOverdue() ? "Yes" : "No") << endl;
    
    cout << "\n=== TEST CASE 16: Multiple Books Same Author ===" << endl;
    Book book7 = Book::createBook("Animal Farm", "George Orwell", "978-0451526342");
    Book book8 = Book::createBook("Homage to Catalonia", "George Orwell", "978-0156421171");
    lib.addBook(book7);
    lib.addBook(book8);
    lib.listBooks();
    
    cout << "\n=== TEST CASE 17: Edge Case - Removing Last Book ===" << endl;
    Library smallLib = Library();
    Book tempBook = Book::createBook("Only Book", "Solo Author", "111-1111111111");
    smallLib.addBook(tempBook);
    smallLib.listBooks();
    smallLib.removeBook("Only Book");
    smallLib.listBooks(); // Should be empty
    
    cout << "\n=== TEST CASE 18: Edge Case - Adding Same Member Twice ===" << endl;
    User duplicateUser = User::createUser("John", "Doe", 1001, "john.doe@university.edu");
    lib.addMember(duplicateUser); // No duplicate check in current implementation
    lib.displayMembers();
    
    cout << "\n=== TEST CASE 19: Checking Overdue Books for Member ===" << endl;
    bool hasOverdue = lib.hasOverdueBooks("Jane Smith");
    cout << "Jane Smith has overdue books: " << (hasOverdue ? "Yes" : "No") << endl;
    
    cout << "\n=== TEST CASE 20: Edge Case - Empty String Searches ===" << endl;
    lib.searchBook("");
    lib.removeMember("");
    
    cout << "\n=== Program Complete ===" << endl;
    
    return 0;
}
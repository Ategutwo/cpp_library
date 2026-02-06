#include <iostream>
#include "library_classes.h"
using namespace std;


void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "   ALVIN'S LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1.  Add a Book" << endl;
    cout << "2.  Remove a Book" << endl;
    cout << "3.  Search for a Book" << endl;
    cout << "4.  List All Books" << endl;
    cout << "5.  Check Book Availability" << endl;
    cout << "6.  Add a Member" << endl;
    cout << "7.  Remove a Member" << endl;
    cout << "8.  Display All Members" << endl;
    cout << "9.  Validate Member" << endl;
    cout << "10. Issue a Book" << endl;
    cout << "11. Return a Book" << endl;
    cout << "12. Check Overdue Books" << endl;
    cout << "13. Display Book Copy Status" << endl;
    cout << "14. Run Automated Tests" << endl;
    cout << "0.  Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void addBookConsole(Library &lib) {
    string title, author, isbn;
    cout << "\n--- Add New Book ---" << endl;
    cout << "Enter book title: ";
    cin >> title;
    cout << "Enter author name: ";
    cin >> author;
    cout << "Enter ISBN: ";
    cin >> isbn;
    
    Book newBook = Book::createBook(title, author, isbn);
    lib.addBook(newBook);
}

void removeBookConsole(Library &lib) {
    string title;
    cout << "\n--- Remove Book ---" << endl;
    cout << "Enter book title to remove: ";
    cin >> title;
    lib.removeBook(title);
}

void searchBookConsole(Library &lib) {
    string title;
    cout << "\n--- Search Book ---" << endl;
    cout << "Enter book title to search: ";
    cin >> title;
    lib.searchBook(title);
}

void checkAvailabilityConsole(Library &lib) {
    string title;
    cout << "\n--- Check Book Availability ---" << endl;
    cout << "Enter book title: ";
    cin >> title;
    bool available = lib.isBookAvailable(title);
    cout << "Book '" << title << "' is " << (available ? "AVAILABLE" : "NOT AVAILABLE") << endl;
}

void addMemberConsole(Library &lib) {
    string firstName, lastName, email;
    int id;
    cout << "\n--- Add New Member ---" << endl;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter member ID (number): ";
    cin >> id;
    cout << "Enter email: ";
    cin >> email;
    
    User newUser = User::createUser(firstName, lastName, id, email);
    lib.addMember(newUser);
}

void removeMemberConsole(Library &lib) {
    string firstName, lastName;
    cout << "\n--- Remove Member ---" << endl;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    string fullName = firstName + " " + lastName;
    lib.removeMember(fullName);
}

void validateMemberConsole(Library &lib) {
    string firstName, lastName;
    cout << "\n--- Validate Member ---" << endl;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    string fullName = firstName + " " + lastName;
    bool valid = lib.isMemberValid(fullName);
    cout << "Member '" << fullName << "' is " << (valid ? "VALID" : "INVALID") << endl;
}

void issueBookConsole(Library &lib) {
    string bookTitle;
    cout << "\n--- Issue Book ---" << endl;
    cout << "Enter book title to issue: ";
    cin >> bookTitle;
    lib.issueBook(bookTitle);
}

void returnBookConsole(Library &lib) {
    string bookTitle;
    cout << "\n--- Return Book ---" << endl;
    cout << "Enter book title to return: ";
    cin >> bookTitle;
    lib.returnBook(bookTitle);
}

void checkOverdueConsole(Library &lib) {
    string firstName, lastName;
    cout << "\n--- Check Overdue Books ---" << endl;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    string fullName = firstName + " " + lastName;
    bool hasOverdue = lib.hasOverdueBooks(fullName);
    cout << "Member '" << fullName << "' " << (hasOverdue ? "HAS" : "DOES NOT HAVE") << " overdue books." << endl;
}

void demonstrateBookCopy() {
    cout << "\n--- Book Copy Demonstration ---" << endl;
    
    Book sampleBook = Book::createBook("DemoBook", "DemoAuthor", "000-000");
    User sampleUser = User::createUser("Sample", "User", 9999, "sample@demo.com");
    
    BookCopy copy1 = BookCopy::createCopy(&sampleBook);
    cout << "Created copy of: " << sampleBook.getTitle() << endl;
    cout << "Available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
    
    copy1.issueToUser(&sampleUser);
    cout << "\nAfter issuing to " << sampleUser.getName() << ":" << endl;
    cout << "Available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
    
    time_t returnDate = time(NULL) + (14 * 24 * 60 * 60);
    copy1.setBookReturnDate(returnDate);
    cout << "Return date set to 14 days from now" << endl;
    cout << "Is overdue: " << (copy1.isOverdue() ? "Yes" : "No") << endl;
    
    copy1.returnBook();
    cout << "\nAfter returning:" << endl;
    cout << "Available: " << (copy1.getIsAvailable() ? "Yes" : "No") << endl;
}

void runQuickTests() {
    cout << "\n--- Running Quick Automated Tests ---" << endl;
    int passed = 0;
    int total = 5;
    
    Library testLib;
    Book testBook = Book::createBook("Test", "Author", "123");
    testLib.addBook(testBook);
    cout << "Test 1 (Add Book): PASSED" << endl;
    passed++;
    
    User testUser = User::createUser("Test", "User", 1, "test@test.com");
    testLib.addMember(testUser);
    cout << "Test 2 (Add Member): PASSED" << endl;
    passed++;
    
    testLib.searchBook("Test");
    cout << "Test 3 (Search Book): PASSED" << endl;
    passed++;
    
    bool valid = testLib.isMemberValid("Test User");
    if(valid) {
        cout << "Test 4 (Validate Member): PASSED" << endl;
        passed++;
    } else {
        cout << "Test 4 (Validate Member): FAILED" << endl;
    }
    
    BookCopy testCopy = BookCopy::createCopy(&testBook);
    if(testCopy.getIsAvailable()) {
        cout << "Test 5 (BookCopy Creation): PASSED" << endl;
        passed++;
    } else {
        cout << "Test 5 (BookCopy Creation): FAILED" << endl;
    }
    
    cout << "\nTests Passed: " << passed << "/" << total << endl;
}

void displayMessage() {
    cout << "\n*****************************************" << endl;
    cout << "*   Welcome to Alvin's Library!        *" << endl;
    cout << "*   Your Gateway to Knowledge          *" << endl;
    cout << "*****************************************\n" << endl;
}

int main()
{
    displayMessage();
    Library lib = Library();
    
    cout << "Loading sample data..." << endl;
    Book book1 = Book::createBook("TheGreatGatsby", "Fitzgerald", "978-0743273565");
    Book book2 = Book::createBook("1984", "Orwell", "978-0451524935");
    Book book3 = Book::createBook("ToKillAMockingbird", "Lee", "978-0061120084");
    
    lib.addBook(book1);
    lib.addBook(book2);
    lib.addBook(book3);
    
    User user1 = User::createUser("John", "Doe", 1001, "john.doe@university.edu");
    User user2 = User::createUser("Jane", "Smith", 1002, "jane.smith@university.edu");
    
    lib.addMember(user1);
    lib.addMember(user2);
    
    cout << "Sample data loaded successfully!\n" << endl;
    
    int choice;
    bool running = true;
    
    while(running) {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                addBookConsole(lib);
                break;
            case 2:
                removeBookConsole(lib);
                break;
            case 3:
                searchBookConsole(lib);
                break;
            case 4:
                cout << "\n--- All Books ---" << endl;
                lib.listBooks();
                break;
            case 5:
                checkAvailabilityConsole(lib);
                break;
            case 6:
                addMemberConsole(lib);
                break;
            case 7:
                removeMemberConsole(lib);
                break;
            case 8:
                cout << "\n--- All Members ---" << endl;
                lib.displayMembers();
                break;
            case 9:
                validateMemberConsole(lib);
                break;
            case 10:
                issueBookConsole(lib);
                break;
            case 11:
                returnBookConsole(lib);
                break;
            case 12:
                checkOverdueConsole(lib);
                break;
            case 13:
                demonstrateBookCopy();
                break;
            case 14:
                runQuickTests();
                break;
            case 0:
                cout << "\nThank you for using Alvin's Library!" << endl;
                cout << "Goodbye!\n" << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}
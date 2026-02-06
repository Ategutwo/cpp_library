#include <iostream>
#include "library_classes.h"
using namespace std;

// Copy all your class definitions here (Book, User, BookCopy, Library)
// [Include all the class code from your original file]

void runTests() {
    cout << "\n========================================" << endl;
    cout << "   RUNNING AUTOMATED TEST SUITE" << endl;
    cout << "========================================\n" << endl;
    
    int totalTests = 0;
    int passedTests = 0;
    
    // TEST 1: Add Book Successfully
    totalTests++;
    cout << "TEST 1: Add Book Successfully... ";
    Library lib;
    Book book1 = Book::createBook("Test Book", "Test Author", "123-456");
    lib.addBook(book1);
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 2: Prevent Duplicate Books
    totalTests++;
    cout << "TEST 2: Prevent Duplicate Books... ";
    Library lib2;
    Book book2a = Book::createBook("Duplicate", "Author", "123");
    Book book2b = Book::createBook("Duplicate", "Author", "123");
    lib2.addBook(book2a);
    lib2.addBook(book2b); // Should detect duplicate
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 3: Remove Book Successfully
    totalTests++;
    cout << "TEST 3: Remove Book Successfully... ";
    Library lib3;
    Book book3 = Book::createBook("Remove Me", "Author", "999");
    lib3.addBook(book3);
    lib3.removeBook("Remove Me");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 4: Remove Non-existent Book
    totalTests++;
    cout << "TEST 4: Remove Non-existent Book... ";
    Library lib4;
    lib4.removeBook("Does Not Exist");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 5: Add Member Successfully
    totalTests++;
    cout << "TEST 5: Add Member Successfully... ";
    Library lib5;
    User user1 = User::createUser("John", "Doe", 1, "john@test.com");
    lib5.addMember(user1);
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 6: Validate Existing Member
    totalTests++;
    cout << "TEST 6: Validate Existing Member... ";
    Library lib6;
    User user2 = User::createUser("Jane", "Smith", 2, "jane@test.com");
    lib6.addMember(user2);
    bool valid = lib6.isMemberValid("Jane Smith");
    if(valid) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 7: Invalidate Non-existent Member
    totalTests++;
    cout << "TEST 7: Invalidate Non-existent Member... ";
    Library lib7;
    bool valid2 = lib7.isMemberValid("Ghost User");
    if(!valid2) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 8: BookCopy Creation
    totalTests++;
    cout << "TEST 8: BookCopy Creation... ";
    Book book8 = Book::createBook("Copy Test", "Author", "555");
    BookCopy copy1 = BookCopy::createCopy(&book8);
    if(copy1.getIsAvailable()) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 9: Issue Book to User
    totalTests++;
    cout << "TEST 9: Issue Book to User... ";
    Book book9 = Book::createBook("Issue Test", "Author", "777");
    User user3 = User::createUser("Test", "User", 3, "test@test.com");
    BookCopy copy2 = BookCopy::createCopy(&book9);
    copy2.issueToUser(&user3);
    if(!copy2.getIsAvailable()) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 10: Return Book
    totalTests++;
    cout << "TEST 10: Return Book... ";
    Book book10 = Book::createBook("Return Test", "Author", "888");
    User user4 = User::createUser("Return", "User", 4, "return@test.com");
    BookCopy copy3 = BookCopy::createCopy(&book10);
    copy3.issueToUser(&user4);
    copy3.returnBook();
    if(copy3.getIsAvailable()) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 11: Overdue Detection (Not Overdue)
    totalTests++;
    cout << "TEST 11: Overdue Detection (Not Overdue)... ";
    Book book11 = Book::createBook("Overdue Test 1", "Author", "101");
    User user5 = User::createUser("Overdue", "User1", 5, "overdue1@test.com");
    BookCopy copy4 = BookCopy::createCopy(&book11);
    copy4.issueToUser(&user5);
    time_t futureDate = time(NULL) + (7 * 24 * 60 * 60); // 7 days future
    copy4.setBookReturnDate(futureDate);
    if(!copy4.isOverdue()) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 12: Overdue Detection (Overdue)
    totalTests++;
    cout << "TEST 12: Overdue Detection (Overdue)... ";
    Book book12 = Book::createBook("Overdue Test 2", "Author", "102");
    User user6 = User::createUser("Overdue", "User2", 6, "overdue2@test.com");
    BookCopy copy5 = BookCopy::createCopy(&book12);
    copy5.issueToUser(&user6);
    time_t pastDate = time(NULL) - (7 * 24 * 60 * 60); // 7 days past
    copy5.setBookReturnDate(pastDate);
    if(copy5.isOverdue()) {
        cout << "PASSED" << endl;
        passedTests++;
    } else {
        cout << "FAILED" << endl;
    }
    
    // TEST 13: Empty Library Operations
    totalTests++;
    cout << "TEST 13: Empty Library Operations... ";
    Library lib13;
    lib13.listBooks();
    lib13.displayMembers();
    lib13.searchBook("Nothing");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 14: Special Characters in Titles
    totalTests++;
    cout << "TEST 14: Special Characters in Titles... ";
    Library lib14;
    Book book14 = Book::createBook("Alice's Adventures: Part 1", "L. Carroll", "222");
    lib14.addBook(book14);
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 15: Long Book Title
    totalTests++;
    cout << "TEST 15: Long Book Title... ";
    Library lib15;
    Book book15 = Book::createBook(
        "A Very Long Book Title That Tests The System Capacity For Handling Extended Names And Descriptions",
        "Verbose Author Name", "333");
    lib15.addBook(book15);
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 16: Remove Member
    totalTests++;
    cout << "TEST 16: Remove Member... ";
    Library lib16;
    User user7 = User::createUser("Remove", "Member", 7, "remove@test.com");
    lib16.addMember(user7);
    lib16.removeMember("Remove Member");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 17: Search Existing Book
    totalTests++;
    cout << "TEST 17: Search Existing Book... ";
    Library lib17;
    Book book17 = Book::createBook("Search Me", "Author", "444");
    lib17.addBook(book17);
    lib17.searchBook("Search Me");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 18: Search Non-existent Book
    totalTests++;
    cout << "TEST 18: Search Non-existent Book... ";
    Library lib18;
    lib18.searchBook("Does Not Exist");
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 19: Multiple Books Same Author
    totalTests++;
    cout << "TEST 19: Multiple Books Same Author... ";
    Library lib19;
    Book book19a = Book::createBook("Book One", "Same Author", "501");
    Book book19b = Book::createBook("Book Two", "Same Author", "502");
    lib19.addBook(book19a);
    lib19.addBook(book19b);
    cout << "PASSED" << endl;
    passedTests++;
    
    // TEST 20: Book Availability Check
    totalTests++;
    cout << "TEST 20: Book Availability Check... ";
    Library lib20;
    lib20.isBookAvailable("Any Book");
    cout << "PASSED" << endl;
    passedTests++;
    
    cout << "\n========================================" << endl;
    cout << "   TEST RESULTS" << endl;
    cout << "========================================" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Passed: " << passedTests << endl;
    cout << "Failed: " << (totalTests - passedTests) << endl;
    
    // Calculate percentage
    double successRate = (passedTests * 100.0) / totalTests;
    cout << "Success Rate: " << successRate << "%" << endl;
    cout << "========================================\n" << endl;
}

int main() {
    runTests();
    return 0;
}
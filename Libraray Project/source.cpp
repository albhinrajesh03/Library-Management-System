#include <iostream>
#include <string>
#include <fstream>

void addtohistory(std::string data)
{
    std::ofstream histfile("history.txt", std::ios::app);
    if (histfile.is_open())
    {
        histfile << data << " || ";
        histfile.flush();
        histfile.close();
        return;
    }
    else
    {
        std::cout << "Cannot access history file" << std::endl;
        return;
    }
}

int multiple_book_with_same_author(std::string author)
{
    int count = 0;
    std::ifstream file("listofbooks.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find(author) != std::string::npos)
            {
                count++;
            }
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return 0;
    }
    return count;
}

void addfirstuser()
{
    std::ofstream file("adminlist.txt", std::ios::app);
    if (file.is_open())
    {
        std::cout << "Creating first user" << std::endl;
        std::string firstuser;
        std::cout << "First username: ";
        std::getline(std::cin, firstuser);
        std::string pass;
        std::cout << "First user Password: ";
        std::getline(std::cin, pass);
        file << "username:" << firstuser << "," << "password:" << pass;
        std::cout << "First user " + firstuser + " added successfully";
        file.flush();
        file.close();
        std::string data;
        data = "First admin " + firstuser + " is added";
        addtohistory(data);
        return;
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

void deleteabook()
{
    std::ifstream adminfile("adminlist.txt");
    if (adminfile.is_open())
    {
        if (adminfile.peek() == std::string::traits_type::eof())
        {
            addfirstuser();
            return;
        }
        std::string username;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::string line;
        while (std ::getline(adminfile, line))
        {
            if (line.find(username) != std::string::npos)
            {
                std::string password;
                std::cout << "Password: ";
                std::getline(std::cin, password);
                std::string check;
                size_t pos = line.find("password:");
                check = line.substr(pos + 9);
                if (check == password)
                {
                    std::ifstream booklist("listofbooks.txt");
                    if (booklist.peek() == std::fstream::traits_type::eof())
                    {
                        std::cout << "File is empty" << std::endl;
                        booklist.close();
                        return;
                    }
                    std::string booktodelete;
                    std::cout << "Enter the book to delete(id or name or author): ";
                    std::getline(std::cin, booktodelete);
                    int count = multiple_book_with_same_author(booktodelete);
                    if (count > 1)
                    {
                        std::string book;
                        std::cout << "There are multiple books of this author please specify using id or book name: ";
                        std::getline(std::cin, book);
                        std::ofstream templist("temp.txt", std::ios::app);
                        if (!booklist.is_open())
                        {
                            std::cout << "Cannot open listofbooks file" << std::endl;
                            return;
                        }
                        if (!templist.is_open())
                        {
                            std::cout << "Cannot open temp file" << std::endl;
                            return;
                        }

                        std::string line;
                        bool bookfound = false;
                        while (std::getline(booklist, line))
                        {
                            if (line.find(book) == std::string::npos)
                            {
                                templist << line << std::endl;
                            }
                            else
                            {
                                bookfound = true;
                            }
                        }

                        booklist.close();
                        templist.flush();
                        templist.close();

                        if (bookfound == true)
                        {
                            std::remove("listofbooks.txt");
                            std::rename("temp.txt", "listofbooks.txt");
                            std::cout << "Book deleted" << std::endl;
                            std::string data;
                            data = username + " deleted " + book + "(id or name)";
                            addtohistory(data);
                            return;
                        }
                        else
                        {
                            std::cout << "Book not found" << std::endl;
                            std::remove("temp.txt");
                            return;
                        }
                    }
                    std::ofstream templist("temp.txt", std::ios::app);
                    if (!booklist.is_open())
                    {
                        std::cout << "Cannot open listofbooks file" << std::endl;
                        return;
                    }
                    if (!templist.is_open())
                    {
                        std::cout << "Cannot open temp file" << std::endl;
                        return;
                    }

                    std::string line;
                    bool bookfound = false;
                    while (std::getline(booklist, line))
                    {
                        if (line.find(booktodelete) == std::string::npos)
                        {
                            templist << line << std::endl;
                        }
                        else
                        {
                            bookfound = true;
                        }
                    }

                    booklist.close();
                    templist.flush();
                    templist.close();

                    if (bookfound == true)
                    {
                        std::remove("listofbooks.txt");
                        std::rename("temp.txt", "listofbooks.txt");
                        std::cout << "Book deleted" << std::endl;
                        std::string data;
                        data = username + " deleted " + booktodelete + "(id or name or author)";
                        addtohistory(data);
                        return;
                    }
                    else
                    {
                        std::cout << "Book not found" << std::endl;
                        std::remove("temp.txt");
                        return;
                    }
                }
                else
                {
                    std::cout << "Wrong password" << std::endl;
                    return;
                }
            }
            else
            {
                std::cout << "User not found" << std::endl;
                return;
            }
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

void findbook()
{
    std::ifstream bookfile("listofbooks.txt");
    if (bookfile.is_open())
    {
        if (bookfile.peek() == std::fstream::traits_type::eof())
        {
            std::cout << "File is empty" << std::endl;
            return;
        }
        else
        {
            std::string booktofind;
            std::cout << "Enter the book to find(id or name or author): ";
            std::getline(std::cin, booktofind);
            std::string line;
            while (std::getline(bookfile, line))
            {
                if (line.find(booktofind) != std::string::npos)
                {
                    std::cout << "Book Found" << std::endl;
                    std::string data;
                    data = booktofind + " is searched";
                    addtohistory(data);
                    std::cout << line;
                    return;
                }
            }
            std::cout << "Book not found" << std::endl;
            return;
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

void availablebooks()
{
    std::ifstream file("listofbooks.txt");
    if (file.is_open())
    {
        std::string line;
        if (file.peek() == std::fstream::traits_type::eof())
        {
            std::cout << "File is empty" << std::endl;
            return;
        }
        else
        {
            while (std::getline(file, line))
            {
                std::cout << line << std::endl;
            }
        }
        std::string data;
        data = "Visited available books";
        addtohistory(data);
        file.close();
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

void addbook()
{
    std::cout << "ONLY ADMIN CAN ADD BOOKS" << std::endl;
    std::ifstream adminfile("adminlist.txt");
    if (adminfile.is_open())
    {
        if (adminfile.peek() == std::string::traits_type::eof())
        {
            addfirstuser();
            return;
        }
        std::string username;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::string line;
        std::string check;
        while (std::getline(adminfile, line))
        {
            if (line.find(username) != std::string::npos)
            {
                size_t pos = line.find("password:");
                check = line.substr(pos + 9);
                std::string password;
                std::cout << "Password: ";
                std::getline(std::cin, password);
                if (check == password)
                {
                    adminfile.close();
                    std::ofstream bookfile("listofbooks.txt", std::ios::app);
                    std::ifstream check("listofbooks.txt");
                    if (bookfile.is_open())
                    {
                        if (check.peek() == std::string::traits_type::eof())
                        {
                            std::cout << "Enter the id: ";
                            int id;
                            std::cin >> id;
                            std::cin.ignore();
                            std::cout << "Enter Book name: ";
                            std::string bookname;
                            std::getline(std::cin, bookname);
                            std::cout << "Enter the author name: ";
                            std::string authorname;
                            std::getline(std::cin, authorname);
                            bookfile << id << "-" << bookname << "-" << authorname;
                            bookfile.flush();
                            bookfile.close();
                            std::cout << "Book added successfully" << std::endl;
                            std::string data;
                            data = id + "-" + bookname + "-" + authorname + "-has been added by " + username;
                            addtohistory(data);
                            return;
                        }
                        std::cout << "Enter the id: ";
                        int id;
                        std::cin >> id;
                        std::cin.ignore();
                        std::cout << "Enter Book name: ";
                        std::string bookname;
                        std::getline(std::cin, bookname);
                        std::cout << "Enter the author name: ";
                        std::string authorname;
                        std::getline(std::cin, authorname);
                        bookfile << std::endl;
                        bookfile << id << "-" << bookname << "-" << authorname;
                        bookfile.flush();
                        bookfile.close();
                        std::cout << "Book added successfully" << std::endl;
                        std::string data;
                        data = id + "-" + bookname + "-" + authorname + "-has been added by " + username;
                        addtohistory(data);
                        return;
                    }
                    else
                    {
                        std::cout << "Cannot open file" << std::endl;
                        return;
                    }
                }
                else
                {
                    std::cout << "wrong password" << std::endl;
                    return;
                }
            }
        }
        std::cout << "Username not found" << std::endl;
        return;
    }
}

void addaadmin()
{
    std::ifstream adminfile("adminlist.txt");
    if (adminfile.is_open())
    {
        if (adminfile.peek() == std::string::traits_type::eof())
        {
            addfirstuser();
            return;
        }
        std::cout << "EXISTING USER INFO" << std::endl;
        std::string username;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::string line;
        while (std ::getline(adminfile, line))
        {
            if (line.find(username) != std::string::npos)
            {
                std::string password;
                std::cout << "Password: ";
                std::getline(std::cin, password);
                std::string check;
                size_t pos = line.find("password:");
                check = line.substr(pos + 9);
                if (check == password)
                {
                    adminfile.close();
                    std::cout << "ADDING A NEW ADMIN" << std::endl;
                    std::string name;
                    std::cout << "New username: ";
                    std::getline(std::cin, name);
                    std::string pass;
                    std::cout << "Set password: ";
                    std::getline(std::cin, pass);
                    std::ofstream file("adminlist.txt", std::ios::app);
                    if (file.is_open())
                    {
                        file << std::endl;
                        file << "username:" << name << "," << "password:" << pass;
                        file.flush();
                        file.close();
                        std::cout << "New user " << name << " is added successfully" << std::endl;
                        std::string data;
                        data = "New user " + name + " is added by " + username;
                        addtohistory(data);
                        return;
                    }
                    else
                    {
                        std::cout << "Cannot open file" << std::endl;
                        return;
                    }
                }
                else
                {
                    adminfile.close();
                    std::cout << "Wrong password" << std::endl;
                    return;
                }
            }
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

void viewhistory()
{
    std::cout << "ONLY ADMIN CAN VIEW HISTORY" << std::endl;
    std::ifstream admin("adminlist.txt");
    if (admin.is_open())
    {
        if (admin.peek() == std::string::traits_type::eof())
        {
            addfirstuser();
            return;
        }
        std::string username;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::string password;
        std::cout << "Password: ";
        std::getline(std::cin, password);
        std::string line;
        while (std::getline(admin, line))
        {
            if (line.find(username) != std::string::npos)
            {
                std::string check;
                size_t pos = line.find("password:");
                check = line.substr(pos + 9);
                if (check == password)
                {
                    std::ifstream hist("history.txt");
                    if (hist.is_open())
                    {
                        if (hist.peek() == std::string::traits_type::eof())
                        {
                            std::cout << "No History" << std::endl;
                            return;
                        }
                        else
                        {
                            std::string histline;
                            while (std::getline(hist, histline))
                            {
                                std::cout << histline << std::endl;
                            }
                            hist.close();
                            std::string data;
                            data = username + " viewed history";
                            addtohistory(data);
                        }
                    }
                    else
                    {
                        std::cout << "Cannot open file" << std::endl;
                        return;
                    }
                }
                else
                {
                    std::cout << "Wrong password" << std::endl;
                    return;
                }
            }
        }
    }
    else
    {
        std::cout << "Cannot open file" << std::endl;
        return;
    }
}

int main()
{
    while (true)
    {
        std::cout << "1-Available Books" << std::endl;
        std::cout << "2-Add book" << std::endl;
        std::cout << "3-Find a book" << std::endl;
        std::cout << "4-Delete a book" << std::endl;
        std::cout << "5-Add a new admin" << std::endl;
        std::cout << "6-History" << std::endl;
        std::cout << "7-Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            availablebooks();
            break;
        case 2:
            addbook();
            break;
        case 3:
            findbook();
            break;
        case 4:
            deleteabook();
            break;
        case 5:
            addaadmin();
            break;
        case 6:
            viewhistory();
            break;
        case 7:
            return 0;
        default:
            std::cout << "Invalied choice" << std::endl;
            break;
        }

        std::cout << "Please enter to continue";
        std::cin.ignore();
        std::cin.get();
    }
}
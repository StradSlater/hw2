#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string isbn, const std::string author): Product("book", name_, price_, qty_),
  isbn_(isbn),
  author_(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const{
  std::string str_keys = name_ + " " + author_ + " " + isbn_;
  std::set<std::string> keywords = parseStringToWords(str_keys);
  return keywords;
}

std::string Book::displayString() const{
  std::string information = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return information;
}

void Book::dump(std::ostream& os) const{
  os << displayString() << std::endl;
}
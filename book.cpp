#include <sstream>
#include <iomanip>
#include <cmath>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author): Product("book", name, price, qty),
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
  std::string information = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n";
  std::stringstream price_str;
  price_str << std::fixed << std::setprecision(2) << price_;
  std::string price_format = price_str.str();
  information += price_format + " " + std::to_string(qty_) + " left.";
  return information;
}

void Book::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}
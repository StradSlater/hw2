#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand): Product("clothing", name, price, qty),
  size_(size),
  brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const{
  std::string str_keys = name_ + " " + brand_ + " " + size_;
  std::set<std::string> keywords = parseStringToWords(str_keys);
  return keywords;
}

std::string Clothing::displayString() const{
  std::string information = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n";
  std::stringstream price_str;
  price_str << std::fixed << std::setprecision(2) << price_;
  std::string price_format = price_str.str();
  information += price_format + " " + std::to_string(qty_) + " left.";
  return information;
}

void Clothing::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}
#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string size, const std::string brand): Product("clothing", name_, price_, qty_),
  size_(size),
  brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const{
  std::string str_keys = name_ + " " + brand_;
  std::set<std::string> keywords = parseStringToWords(str_keys);
  return keywords;
}

std::string Clothing::displayString() const{
  std::string information = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return information;
}

void Clothing::dump(std::ostream& os) const{
  os << displayString() << std::endl;
}
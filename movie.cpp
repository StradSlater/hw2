#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating): Product("movie", name, price, qty),
  genre_(genre),
  rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const{
  std::string str_keys = name_ + " " + genre_;
  std::set<std::string> keywords = parseStringToWords(str_keys);
  return keywords;
}

std::string Movie::displayString() const{
  std::string information = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n";
  std::stringstream price_str;
  price_str << std::fixed << std::setprecision(2) << price_;
  std::string price_format = price_str.str();
  information += price_format + " " + std::to_string(qty_) + " left.";
  return information;
}

void Movie::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}
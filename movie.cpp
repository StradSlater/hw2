#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string genre, const std::string rating): Product("movie", name_, price_, qty_),
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
  std::string information = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return information;
}

void Movie::dump(std::ostream& os) const{
  os << displayString() << std::endl;
}
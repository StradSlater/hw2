#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"


int main (){
  Clothing* b = new Clothing("movie", "Room at the Bottom", 100.0, 3, "111-33d", "Strad");
  std::set<std::string>::iterator it;
  std::set<std::string> keywords = b->keywords();
  for (it = keywords.begin(); it != keywords.end(); ++it){
    std::cout << *it << std::endl;
  }
  std::cout << b->getName()<< std::endl;
  std::cout << std::endl;
  std::cout << b->displayString()<< std::endl;
  b->dump(std::cout);
  
  return 0;
}
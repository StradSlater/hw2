#include <sstream>
#include <iomanip>
#include "mydatastore.h"

MyDataStore::MyDataStore(){

}


//clean up all allocated product object
MyDataStore::~MyDataStore(){
  
  std::map<User*, std::vector<Product*>>::iterator it2;
  for (it2 = users_.begin(); it2 != users_.end(); ++it2){
    User* u = it2->first;
    delete u;
  }

  std::set<Product*>::iterator it3;
  for (it3 = products_.begin(); it3 != products_.end(); ++it3){
    Product* p = *it3;
    delete p;
  }

}

//adding a product to the database
void MyDataStore::addProduct(Product* p){
  products_.insert(p);
  std::set<std::string> p_keys = p->keywords();
  std::set<std::string>::iterator it1;
  for (it1 = p_keys.begin(); it1 != p_keys.end(); ++it1){
    std::string key = *it1;
    key = convToLower(key);
    keyProds_[key].insert(p);

    
  }
}

//adding a user to the database
void MyDataStore::addUser(User* u){
  users_[u];
}

//search through the data base with keywords
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  
  std::set<Product*> final;
  std::vector<std::string>::iterator it1;
  std::set<std::set<Product*>> prod_sets;
  for(it1 = terms.begin(); it1 != terms.end(); ++it1){
      std::string key = *it1;
      std::map<std::string, std::set<Product*>>::iterator it = keyProds_.find(key);
      if (it != keyProds_.end()){
        prod_sets.insert(it->second);
      }
      else {
      }
  }
  if (!type && (prod_sets.size() > 0)){
    std::set<std::set<Product*>>::iterator it1 = prod_sets.begin();
    std::set<Product*> prod_set = *it1;
    final = setIntersection(products_, prod_set);
    for (it1 = prod_sets.begin(); it1 != prod_sets.end(); ++it1){
      prod_set = *it1;
      final = setIntersection(final, prod_set);
    }
  }
  else if (type && (prod_sets.size() > 0)) {
    std::set<std::set<Product*>>::iterator it1 = prod_sets.begin();
    std::set<Product*> prod_set = *it1;
    std::set<Product*> empty;
    final = setUnion(empty, prod_set);
    for (it1 = prod_sets.begin(); it1 != prod_sets.end(); ++it1){
      prod_set = *it1;
      final = setUnion(final, prod_set);
    }
  }
  else{
    std::vector<Product*> hits;
    return hits;
  }

  std::vector<Product*> hits(final.begin(), final.end());

  return hits;
}

//adding a product to the cart
void MyDataStore::addtoCart(std::string user_name, int index, std::vector<Product*>& hits){
    
    Product* p = hits[index-1];
    std::map<User*, std::vector<Product*>>::iterator it1;
    for (it1 = users_.begin(); it1 != users_.end(); ++it1){
        User* u = it1->first;
        std::string name = u->getName();
        if (user_name == name){
          users_[u].push_back(p);
          return;
      }
    }
    if (it1 == users_.end()){
      std::cout << "Invalid request" << std::endl;
    }


}

//putting the data from the database onto an output file/quit
void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  std::set<Product*>::iterator it;
  for (it = products_.begin(); it != products_.end(); ++it){
    Product* p = *it;
    p->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      u->dump(ofile);
      
  }
  ofile << "</users>" << std::endl;

}

//viewing what is left in the cart
void MyDataStore::viewcart(std::string user_name, std::ostream& os){
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      std::string name = u->getName();
      if (user_name == name){
        std::vector<Product*> cart= it1->second;
        std::vector<Product*>::iterator it1;
        int index = 1;
        for (it1 = cart.begin(); it1 != cart.end(); ++it1){
          Product* p = *it1;
          std::cout << "Item: " << index << std::endl;
          std::string output = p->displayString();
          std::cout << output << std::endl;
          index++;
        }
        break;
      }
      else if (it1 == std::prev(users_.end())){
        std::cout << "Invalid username" << std::endl;
      }
  }
}

//buying what one can in the cart
void MyDataStore::buycart(std::string user_name){
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      std::string name = u->getName();
      if (user_name == name){
        std::vector<Product*>& cart= it1->second;
        std::vector<Product*>::iterator it = cart.begin();
        while(it != cart.end()){
            Product* p = *it;
            if ((p->getQty() > 0) && ((u->getBalance() - p->getPrice()) >= 0)){
              p->subtractQty(1);
              u->deductAmount(p->getPrice());
              it = cart.erase(it);
            }
            else{
              ++it;
            }
        }
        
       
      }
      else if (it1 == std::prev(users_.end())){
        std::cout << "Invalid username" << std::endl;
      }
  }
  
  
}
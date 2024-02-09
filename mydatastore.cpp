#include <sstream>
#include <iomanip>
#include "mydatastore.h"

MyDataStore::MyDataStore(){

}

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

void MyDataStore::addUser(User* u){
  users_[u];
}

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

void MyDataStore::addtoCart(std::string user_name, int index, std::vector<Product*>& hits){
  Product* p = hits[index-1];
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      std::string name = u->getName();
      if (user_name == name){
        users_[u].insert(users_[u].begin(), p);
        
    }
  }
  
}


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

void MyDataStore::viewcart(std::string user_name, std::ostream& os){
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      std::string name = u->getName();
      if (user_name == name){
        std::vector<Product*> cart= it1->second;
        std::vector<Product*>::iterator it1;
        for (it1 = cart.begin(); it1 != cart.end(); ++it1){
          Product* p = *it1;
          std::string output = p->displayString();
          std::cout << output << std::endl;
        }
      }
  }
}
void MyDataStore::buycart(std::string user_name){
  std::map<User*, std::vector<Product*>>::iterator it1;
  for (it1 = users_.begin(); it1 != users_.end(); ++it1){
      User* u = it1->first;
      std::string name = u->getName();
      if (user_name == name){
        std::vector<Product*> cart= it1->second;
        std::vector<Product*>::iterator it;
        for (it = cart.begin(); it != cart.end(); ++it){
          Product* p = *it;
          if ((p->getQty() > 0) && ((u->getBalance() - p->getPrice()) >= 0)){
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
            
          }
          
      }
    }
    else if (it1 == users_.end()){
      std::cout << "Invalid username" << std::endl;
    }
  }
  
  
}
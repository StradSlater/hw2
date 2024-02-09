#include <map>

#include "datastore.h"
#include "util.h"


class MyDataStore : public DataStore{

  public:
    MyDataStore();

    ~MyDataStore();

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void viewcart(std::string user_name, std::ostream& os);

    void buycart(std::string user_name);

    void addtoCart(std::string user_name, int index, std::vector<Product*>& hits);



  private: 
    std::set<Product*> products_;
    std::map<User*, std::vector<Product*>> users_;
    std::map<std::string, std::set<Product*>> keyProds_;

};


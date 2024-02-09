#include "product.h"
#include "util.h"

class Clothing : public Product{
  public:
    Clothing(const std::string size, const std::string brand); 
    ~Clothing(); 
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  protected:
    std::string size_;
    std::string brand_;
};

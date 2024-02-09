#include "product.h"
#include "util.h"

class Book : public Product{
  public:
    Book(const std::string isbn, const std::string author); 
    ~Book(); 
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  protected:
    std::string isbn_;
    std::string author_;
};
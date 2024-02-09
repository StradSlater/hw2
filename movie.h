#include "product.h"
#include "util.h"

class Movie : public Product{
  public:
    Movie(const std::string genre, const std::string rating); 
    ~Movie(); 
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  protected:
    std::string genre_;
    std::string rating_;
};
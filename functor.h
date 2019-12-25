#include <string>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  {

    int lhssum = 0;
    int rhssum = 0;
    char numbers[36] = {'0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
    'P','Q','R','S','T','U','V','W','X','Y','Z'};

    for(unsigned int i = 0; i<lhs.size(); i++){
      for(int z = 0; z <=35; z++){
        if(std::toupper(lhs[i]) == numbers[z]){
          lhssum = lhssum + z;
        }
      }
    }
  
  
    for(unsigned int j = 0; j<rhs.size(); j++){
      for(int g = 0; g <=35; g++){
        if(std::toupper(rhs[j]) == numbers[g]){
          rhssum = rhssum + g;
        }
      }
    }


if(rhssum == lhssum){
  return(lhs < rhs);
}

return (lhssum < rhssum);

  }

};

struct pairComp {
  
  bool operator()(const std::pair<int,int> a, const std::pair<int,int> b)
  {
      return (a.first < b.first);
  }

};
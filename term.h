#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term {

public:

  Term();
  
  virtual string symbol() const = 0;

  virtual string value() const;

  virtual bool match(Term & term);
};

#endif

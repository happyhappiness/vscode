{
  if (this == &rxp) {
    return *this;
  }
  if (!rxp.program) {
    this->program = 0;
    return *this;
  }
  int ind;
  this->progsize = rxp.progsize; // Copy regular expression size
  delete[] this->program;
  this->program = new char[this->progsize]; // Allocate storage
  for (ind = this->progsize; ind-- != 0;)   // Copy regular expresion
    this->program[ind] = rxp.program[ind];
  this->startp[0] = rxp.startp[0]; // Copy pointers into last
  this->endp[0] = rxp.endp[0];     // Successful "find" operation
  this->regmust = rxp.regmust;     // Copy field
  if (rxp.regmust != 0) {
    char* dum = rxp.program;
    ind = 0;
    while (dum != rxp.regmust) {
      ++dum;
      ++ind;
    }
    this->regmust = this->program + ind;
  }
  this->regstart = rxp.regstart; // Copy starting index
  this->reganch = rxp.reganch;   // Copy remaining private data
  this->regmlen = rxp.regmlen;   // Copy remaining private data

  return *this;
}
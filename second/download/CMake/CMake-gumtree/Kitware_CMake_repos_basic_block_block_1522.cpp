{
    char* dum = rxp.program;
    ind = 0;
    while (dum != rxp.regmust) {
      ++dum;
      ++ind;
    }
    this->regmust = this->program + ind;
  }
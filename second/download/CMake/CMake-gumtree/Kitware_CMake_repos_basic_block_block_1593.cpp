((s = strchr(s, this->regstart)) != 0) {
      if (regtry(s, this->startp, this->endp, this->program))
        return (1);
      s++;
    }
{
      longest = 0;
      len = 0;
      for (; scan != 0; scan = regnext(scan))
        if (OP(scan) == EXACTLY && strlen(OPERAND(scan)) >= len) {
          longest = OPERAND(scan);
          len = strlen(OPERAND(scan));
        }
      this->regmust = longest;
      this->regmlen = len;
    }
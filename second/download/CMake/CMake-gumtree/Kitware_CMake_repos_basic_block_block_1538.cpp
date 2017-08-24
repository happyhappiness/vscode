(OP(scan) == EXACTLY)
      this->regstart = *OPERAND(scan);
    else if (OP(scan) == BOL)
      this->reganch++
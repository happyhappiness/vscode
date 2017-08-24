{
      int rxpclass;
      int rxpclassend;

      if (*regparse == '^') { // Complement of range.
        ret = regnode(ANYBUT);
        regparse++;
      } else
        ret = regnode(ANYOF);
      if (*regparse == ']' || *regparse == '-')
        regc(*regparse++);
      while (*regparse != '\0' && *regparse != ']') {
        if (*regparse == '-') {
          regparse++;
          if (*regparse == ']' || *regparse == '\0')
            regc('-');
          else {
            rxpclass = UCHARAT(regparse - 2) + 1;
            rxpclassend = UCHARAT(regparse);
            if (rxpclass > rxpclassend + 1) {
              // RAISE Error, SYM(RegularExpression), SYM(Invalid_Range),
              printf("RegularExpression::compile(): Invalid range in [].\n");
              return 0;
            }
            for (; rxpclass <= rxpclassend; rxpclass++)
              regc(static_cast<char>(rxpclass));
            regparse++;
          }
        } else
          regc(*regparse++);
      }
      regc('\0');
      if (*regparse != ']') {
        // RAISE Error, SYM(RegularExpression), SYM(Unmatched_Bracket),
        printf("RegularExpression::compile(): Unmatched [].\n");
        return 0;
      }
      regparse++;
      *flagp |= HASWIDTH | SIMPLE;
    }
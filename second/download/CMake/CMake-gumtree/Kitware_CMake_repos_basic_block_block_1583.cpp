{
  char* ret;
  int flags;

  *flagp = WORST; // Tentatively.

  switch (*regparse++) {
    case '^':
      ret = regnode(BOL);
      break;
    case '$':
      ret = regnode(EOL);
      break;
    case '.':
      ret = regnode(ANY);
      *flagp |= HASWIDTH | SIMPLE;
      break;
    case '[': {
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
    } break;
    case '(':
      ret = reg(1, &flags);
      if (ret == 0)
        return (0);
      *flagp |= flags & (HASWIDTH | SPSTART);
      break;
    case '\0':
    case '|':
    case ')':
      // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
      printf("RegularExpression::compile(): Internal error.\n"); // Never here
      return 0;
    case '?':
    case '+':
    case '*':
      // RAISE Error, SYM(RegularExpression), SYM(No_Operand),
      printf("RegularExpression::compile(): ?+* follows nothing.\n");
      return 0;
    case '\\':
      if (*regparse == '\0') {
        // RAISE Error, SYM(RegularExpression), SYM(Trailing_Backslash),
        printf("RegularExpression::compile(): Trailing backslash.\n");
        return 0;
      }
      ret = regnode(EXACTLY);
      regc(*regparse++);
      regc('\0');
      *flagp |= HASWIDTH | SIMPLE;
      break;
    default: {
      int len;
      char ender;

      regparse--;
      len = int(strcspn(regparse, META));
      if (len <= 0) {
        // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
        printf("RegularExpression::compile(): Internal error.\n");
        return 0;
      }
      ender = *(regparse + len);
      if (len > 1 && ISMULT(ender))
        len--; // Back off clear of ?+* operand.
      *flagp |= HASWIDTH;
      if (len == 1)
        *flagp |= SIMPLE;
      ret = regnode(EXACTLY);
      while (len > 0) {
        regc(*regparse++);
        len--;
      }
      regc('\0');
    } break;
  }
  return (ret);
}
static char* reg(int paren, int* flagp)
{
  char* ret;
  char* br;
  char* ender;
  int parno = 0;
  int flags;

  *flagp = HASWIDTH; // Tentatively.

  // Make an OPEN node, if parenthesized.
  if (paren) {
    if (regnpar >= RegularExpression::NSUBEXP) {
      // RAISE Error, SYM(RegularExpression), SYM(Too_Many_Parens),
      printf("RegularExpression::compile(): Too many parentheses.\n");
      return 0;
    }
    parno = regnpar;
    regnpar++;
    ret = regnode(static_cast<char>(OPEN + parno));
  } else
    ret = 0;

  // Pick up the branches, linking them together.
  br = regbranch(&flags);
  if (br == 0)
    return (0);
  if (ret != 0)
    regtail(ret, br); // OPEN -> first.
  else
    ret = br;
  if (!(flags & HASWIDTH))
    *flagp &= ~HASWIDTH;
  *flagp |= flags & SPSTART;
  while (*regparse == '|') {
    regparse++;
    br = regbranch(&flags);
    if (br == 0)
      return (0);
    regtail(ret, br); // BRANCH -> BRANCH.
    if (!(flags & HASWIDTH))
      *flagp &= ~HASWIDTH;
    *flagp |= flags & SPSTART;
  }

  // Make a closing node, and hook it on the end.
  ender = regnode(static_cast<char>((paren) ? CLOSE + parno : END));
  regtail(ret, ender);

  // Hook the tails of the branches to the closing node.
  for (br = ret; br != 0; br = regnext(br))
    regoptail(br, ender);

  // Check for proper termination.
  if (paren && *regparse++ != ')') {
    // RAISE Error, SYM(RegularExpression), SYM(Unmatched_Parens),
    printf("RegularExpression::compile(): Unmatched parentheses.\n");
    return 0;
  } else if (!paren && *regparse != '\0') {
    if (*regparse == ')') {
      // RAISE Error, SYM(RegularExpression), SYM(Unmatched_Parens),
      printf("RegularExpression::compile(): Unmatched parentheses.\n");
      return 0;
    } else {
      // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
      printf("RegularExpression::compile(): Internal error.\n");
      return 0;
    }
    // NOTREACHED
  }
  return (ret);
}
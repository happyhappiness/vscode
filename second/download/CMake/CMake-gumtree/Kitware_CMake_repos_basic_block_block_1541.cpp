{
  const char* scan;
  const char* longest;
  size_t len;
  int flags;

  if (exp == 0) {
    // RAISE Error, SYM(RegularExpression), SYM(No_Expr),
    printf("RegularExpression::compile(): No expression supplied.\n");
    return false;
  }

  // First pass: determine size, legality.
  regparse = exp;
  regnpar = 1;
  regsize = 0L;
  regcode = &regdummy;
  regc(static_cast<char>(MAGIC));
  if (!reg(0, &flags)) {
    printf("RegularExpression::compile(): Error in compile.\n");
    return false;
  }
  this->startp[0] = this->endp[0] = this->searchstring = 0;

  // Small enough for pointer-storage convention?
  if (regsize >= 32767L) { // Probably could be 65535L.
    // RAISE Error, SYM(RegularExpression), SYM(Expr_Too_Big),
    printf("RegularExpression::compile(): Expression too big.\n");
    return false;
  }

  // Allocate space.
  //#ifndef _WIN32
  if (this->program != 0)
    delete[] this->program;
  //#endif
  this->program = new char[regsize];
  this->progsize = static_cast<int>(regsize);

  if (this->program == 0) {
    // RAISE Error, SYM(RegularExpression), SYM(Out_Of_Memory),
    printf("RegularExpression::compile(): Out of memory.\n");
    return false;
  }

  // Second pass: emit code.
  regparse = exp;
  regnpar = 1;
  regcode = this->program;
  regc(static_cast<char>(MAGIC));
  reg(0, &flags);

  // Dig out information for optimizations.
  this->regstart = '\0'; // Worst-case defaults.
  this->reganch = 0;
  this->regmust = 0;
  this->regmlen = 0;
  scan = this->program + 1;       // First BRANCH.
  if (OP(regnext(scan)) == END) { // Only one top-level choice.
    scan = OPERAND(scan);

    // Starting-point info.
    if (OP(scan) == EXACTLY)
      this->regstart = *OPERAND(scan);
    else if (OP(scan) == BOL)
      this->reganch++;

    //
    // If there's something expensive in the r.e., find the longest
    // literal string that must appear and make it the regmust.  Resolve
    // ties in favor of later strings, since the regstart check works
    // with the beginning of the r.e. and avoiding duplication
    // strengthens checking.  Not a strong reason, but sufficient in the
    // absence of others.
    //
    if (flags & SPSTART) {
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
  }
  return true;
}
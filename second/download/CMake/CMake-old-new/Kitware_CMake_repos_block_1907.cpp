{ // Probably could be 65535L.
    // RAISE Error, SYM(RegularExpression), SYM(Expr_Too_Big),
    printf("RegularExpression::compile(): Expression too big.\n");
    return false;
  }
(!(flags & HASWIDTH) && op != '?') {
    // RAISE Error, SYM(RegularExpression), SYM(Empty_Operand),
    printf("RegularExpression::compile() : *+ operand could be empty.\n");
    return 0;
  }
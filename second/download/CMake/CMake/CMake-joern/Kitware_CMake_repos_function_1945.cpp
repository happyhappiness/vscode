static char* regpiece(int* flagp)
{
  char* ret;
  char op;
  char* next;
  int flags;

  ret = regatom(&flags);
  if (ret == 0)
    return (0);

  op = *regparse;
  if (!ISMULT(op)) {
    *flagp = flags;
    return (ret);
  }

  if (!(flags & HASWIDTH) && op != '?') {
    // RAISE Error, SYM(RegularExpression), SYM(Empty_Operand),
    printf("RegularExpression::compile() : *+ operand could be empty.\n");
    return 0;
  }
  *flagp = (op != '+') ? (WORST | SPSTART) : (WORST | HASWIDTH);

  if (op == '*' && (flags & SIMPLE))
    reginsert(STAR, ret);
  else if (op == '*') {
    // Emit x* as (x&|), where & means "self".
    reginsert(BRANCH, ret);         // Either x
    regoptail(ret, regnode(BACK));  // and loop
    regoptail(ret, ret);            // back
    regtail(ret, regnode(BRANCH));  // or
    regtail(ret, regnode(NOTHING)); // null.
  } else if (op == '+' && (flags & SIMPLE))
    reginsert(PLUS, ret);
  else if (op == '+') {
    // Emit x+ as x(&|), where & means "self".
    next = regnode(BRANCH); // Either
    regtail(ret, next);
    regtail(regnode(BACK), ret);    // loop back
    regtail(next, regnode(BRANCH)); // or
    regtail(ret, regnode(NOTHING)); // null.
  } else if (op == '?') {
    // Emit x? as (x|)
    reginsert(BRANCH, ret);        // Either x
    regtail(ret, regnode(BRANCH)); // or
    next = regnode(NOTHING);       // null.
    regtail(ret, next);
    regoptail(ret, next);
  }
  regparse++;
  if (ISMULT(*regparse)) {
    // RAISE Error, SYM(RegularExpression), SYM(Nested_Operand),
    printf("RegularExpression::compile(): Nested *?+.\n");
    return 0;
  }
  return (ret);
}
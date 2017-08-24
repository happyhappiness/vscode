{
  // "Operandless" and "op != BRANCH" are synonymous in practice.
  if (p == 0 || p == &regdummy || OP(p) != BRANCH)
    return;
  regtail(OPERAND(p), val);
}
{
  char* src;
  char* dst;
  char* place;

  if (regcode == &regdummy) {
    regsize += 3;
    return;
  }

  src = regcode;
  regcode += 3;
  dst = regcode;
  while (src > opnd)
    *--dst = *--src;

  place = opnd; // Op node, where operand used to be.
  *place++ = op;
  *place++ = '\0';
  *place = '\0';
}
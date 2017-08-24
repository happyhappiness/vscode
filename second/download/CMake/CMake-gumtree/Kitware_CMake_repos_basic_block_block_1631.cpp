{
  int offset;

  if (p == &regdummy)
    return (0);

  offset = NEXT(p);
  if (offset == 0)
    return (0);

  if (OP(p) == BACK)
    return (p - offset);
  else
    return (p + offset);
}
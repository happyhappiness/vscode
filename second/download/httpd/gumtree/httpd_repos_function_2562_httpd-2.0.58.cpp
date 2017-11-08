static void dtdSwap(DTD *p1, DTD *p2)
{
  DTD tem;
  memcpy(&tem, p1, sizeof(DTD));
  memcpy(p1, p2, sizeof(DTD));
  memcpy(p2, &tem, sizeof(DTD));
}
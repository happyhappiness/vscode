{
  if (!Ppmd_RangeDec_Init(p))
    return False;
  p->Bottom = 0x8000;
  return True;
}
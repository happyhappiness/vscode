{
  if (p->Stream->Read((void *)p->Stream) != 0)
    return False;
  return Ppmd_RangeDec_Init(p);
}
int quadoption (int opt)
{
  int n = opt/4;
  int b = (opt % 4) * 2;

  return (QuadOptions[n] >> b) & 0x3;
}
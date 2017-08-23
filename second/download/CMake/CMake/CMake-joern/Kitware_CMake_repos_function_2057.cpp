int main()
{
  // test static data (needs declspec to work)
  Hello::Data = 120;
  Hello h;
  h.real();
  hello();
  printf(" ");
  world();
  printf("\n");
  foo();
  printf("\n");
  bar();
  objlib();
  printf("\n");
#ifdef HAS_JUSTNOP
  justnop();
#endif
  return 0;
}
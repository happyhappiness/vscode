void tool_pressanykey(void)
{
#if defined(__SYMBIAN32__)
  getchar();
#elif defined(NETWARE)
  pressanykey();
#endif
}
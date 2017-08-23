int main()
{
  printf("Hello from subdirectory\n");
  secondone();
#ifdef CMAKE_PAREN
  testOdd();
#endif
  pair_stuff();
  pair_p_stuff();
  vcl_stuff();
  return 0;
}
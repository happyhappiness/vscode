{
  if (Lib1Func() != 2.0) {
    printf("Problem with lib1\n");
    return 1;
  }
  if (Lib2Func() != 1.0) {
    printf("Problem with lib2\n");
    return 1;
  }
  if (Lib4Func() != 4.0) {
    printf("Problem with lib4\n");
    return 1;
  }
  printf("The value of Foo: %s\n", foo);
  return SomeFunctionInFoo() - 5;
}
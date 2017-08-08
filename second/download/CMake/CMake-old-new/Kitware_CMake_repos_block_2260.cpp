{
  /* Reference a GL symbol without requiring a context at runtime.  */
  printf("&glGetString = %p\n", &glGetString);
  return 0;
}
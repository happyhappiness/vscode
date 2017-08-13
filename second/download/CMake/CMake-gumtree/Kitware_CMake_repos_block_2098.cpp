{
  printf("%s: decoding bad  ", passed ? "pass" : "FAIL");
  test_utf8_char_print(c);
  printf(" ");
}
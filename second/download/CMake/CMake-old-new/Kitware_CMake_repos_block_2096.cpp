{
  printf("%s: decoding good ", passed ? "pass" : "FAIL");
  test_utf8_char_print(c);
  printf(" (%s) ", c);
}
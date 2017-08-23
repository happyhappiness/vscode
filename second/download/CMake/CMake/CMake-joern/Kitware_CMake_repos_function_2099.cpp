static void report_bad(bool passed, test_utf8_char const c)
{
  printf("%s: decoding bad  ", passed ? "pass" : "FAIL");
  test_utf8_char_print(c);
  printf(" ");
}
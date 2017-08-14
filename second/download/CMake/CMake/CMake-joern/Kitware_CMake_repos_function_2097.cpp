static void report_good(bool passed, test_utf8_char const c)
{
  printf("%s: decoding good ", passed ? "pass" : "FAIL");
  test_utf8_char_print(c);
  printf(" (%s) ", c);
}
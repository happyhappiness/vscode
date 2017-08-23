static void test_utf8_char_print(test_utf8_char const c)
{
  unsigned char const* d = reinterpret_cast<unsigned char const*>(c);
  printf("[0x%02X,0x%02X,0x%02X,0x%02X]", (int)d[0], (int)d[1], (int)d[2],
         (int)d[3]);
}
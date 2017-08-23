static bool decode_good(test_utf8_entry const entry)
{
  unsigned int uc;
  if (const char* e =
        cm_utf8_decode_character(entry.str, entry.str + 4, &uc)) {
    int used = static_cast<int>(e - entry.str);
    if (uc != entry.chr) {
      report_good(false, entry.str);
      printf("expected 0x%04X, got 0x%04X\n", entry.chr, uc);
      return false;
    }
    if (used != entry.n) {
      report_good(false, entry.str);
      printf("had %d bytes, used %d\n", entry.n, used);
      return false;
    }
    report_good(true, entry.str);
    printf("got 0x%04X\n", uc);
    return true;
  }
  report_good(false, entry.str);
  printf("failed\n");
  return false;
}
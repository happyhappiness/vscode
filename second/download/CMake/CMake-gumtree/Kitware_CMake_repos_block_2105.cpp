{
  unsigned int uc = 0xFFFFu;
  const char* e = cm_utf8_decode_character(s, s + 4, &uc);
  if (e) {
    report_bad(false, s);
    printf("expected failure, got 0x%04X\n", uc);
    return false;
  }
  report_bad(true, s);
  printf("failed as expected\n");
  return true;
}
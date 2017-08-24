{
  if (!str || !tmt || strlen(str) > 26) {
    return false;
  }

  struct tm tmt2;

  // __TIMESTAMP__
  // The date and time of the last modification of the current source file,
  // expressed as a string literal in the form Ddd Mmm Date hh:mm:ss yyyy,
  /// where Ddd is the abbreviated day of the week and Date is an integer
  // from 1 to 31.

  // index:   0123456789
  //                    0123456789
  //                              0123456789
  // format:  Ddd Mmm Date hh:mm:ss yyyy
  // example: Fri Dec 19 14:34:58 2003

  static char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

  char buffer[27];
  strcpy(buffer, str);

  buffer[7] = 0;
  char* ptr = strstr(month_names, buffer + 4);
  if (!ptr) {
    return false;
  }

  int month = static_cast<int>((ptr - month_names) / 3);
  int day = atoi(buffer + 8);
  int hour = atoi(buffer + 11);
  int min = atoi(buffer + 14);
  int sec = atoi(buffer + 17);
  int year = atoi(buffer + 20);

  tmt2.tm_isdst = -1;
  tmt2.tm_hour = hour;
  tmt2.tm_min = min;
  tmt2.tm_sec = sec;
  tmt2.tm_wday = 0;
  tmt2.tm_yday = 0;
  tmt2.tm_mday = day;
  tmt2.tm_mon = month;
  tmt2.tm_year = year - 1900;

  *tmt = mktime(&tmt2);
  return true;
}
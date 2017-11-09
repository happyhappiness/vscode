static int checkmonth(const char *check)
{
  int i;
  const char * const *what;
  bool found = FALSE;

  what = &Curl_month[0];
  for(i = 0; i<12; i++) {
    if(strcasecompare(check, what[0])) {
      found = TRUE;
      break;
    }
    what++;
  }
  return found?i:-1; /* return the offset or -1, no real offset is -1 */
}
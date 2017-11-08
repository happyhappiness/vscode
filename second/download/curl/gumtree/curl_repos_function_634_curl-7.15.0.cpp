static int checktz(char *check)
{
  unsigned int i;
  const struct tzinfo *what;
  bool found= FALSE;

  what = tz;
  for(i=0; i< sizeof(tz)/sizeof(tz[0]); i++) {
    if(curl_strequal(check, what->name)) {
      found=TRUE;
      break;
    }
    what++;
  }
  return found?what->offset*60:-1;
}
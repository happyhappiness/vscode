static char *
set_thread_string(localkey_t key, const char * s)

{
  int i;
  char * cp;

  if(!s)
    return (char *) NULL;

  i = strlen(s) + 1;
  cp = Curl_thread_buffer(key, MAX_CONV_EXPANSION * i + 1);

  if(cp) {
    i = QadrtConvertE2A(cp, s, MAX_CONV_EXPANSION * i, i);
    cp[i] = '\0';
  }

  return cp;
}
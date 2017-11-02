char *
curl_version_ccsid(unsigned int ccsid)

{
  int i;
  char * aversion;
  char * eversion;

  aversion = curl_version();

  if(!aversion)
    return aversion;

  i = strlen(aversion) + 1;
  i *= MAX_CONV_EXPANSION;

  if(!(eversion = Curl_thread_buffer(LK_CURL_VERSION, i)))
    return (char *) NULL;

  if(convert(eversion, i, ccsid, aversion, -1, ASCII_CCSID) < 0)
    return (char *) NULL;

  return eversion;
}
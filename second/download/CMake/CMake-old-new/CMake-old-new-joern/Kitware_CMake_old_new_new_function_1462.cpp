int GetFtpFile(void)
{
  int retVal = 0;
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) 
    {
    /* Get curl 7.9.2 from sunet.se's FTP site: */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(curl, CURLOPT_URL,
                     "ftp://public.kitware.com/pub/cmake/cygwin/setup.hint");
    res = curl_easy_perform(curl);
    if ( res != 0 )
      {
      printf("Error fetching: ftp://public.kitware.com/pub/cmake/cygwin/setup.hint\n");
      retVal = 1;
      }

    /* always cleanup */
    curl_easy_cleanup(curl);
    }
  else
    {
    printf("Cannot create curl object\n");
    retVal = 1;
    }
  return retVal;
}
int main(int argc, char **argv )
{
  CURL *curl;
  char curl_errbuf[CURL_ERROR_SIZE];
  TidyDoc tdoc;
  TidyBuffer docbuf = {0};
  TidyBuffer tidy_errbuf = {0};
  int err;
  if ( argc == 2) {
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

    tdoc = tidyCreate();
    tidyOptSetBool(tdoc, TidyForceOutput, yes); /* try harder */
    tidyOptSetInt(tdoc, TidyWrapLen, 4096);
    tidySetErrorBuffer( tdoc, &tidy_errbuf );
    tidyBufInit(&docbuf);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);
    err=curl_easy_perform(curl);
    if ( !err ) {
      err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */
      if ( err >= 0 ) {
        err = tidyCleanAndRepair(tdoc); /* fix any problems */
        if ( err >= 0 ) {
          err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */
          if ( err >= 0 ) {
            dumpNode( tdoc, tidyGetRoot(tdoc), 0 ); /* walk the tree */
            fprintf(stderr, "%s\n", tidy_errbuf.bp); /* show errors */
          }
        }
      }
    }
    else
      fprintf(stderr, "%s\n", curl_errbuf);

    /* clean-up */
    curl_easy_cleanup(curl);
    tidyBufFree(&docbuf);
    tidyBufFree(&tidy_errbuf);
    tidyRelease(tdoc);
    return(err);

  }
  else
    printf( "usage: %s <url>\n", argv[0] );

  return(0);
}
int test(char *URL)
{
  int res;
  CURLSHcode scode = CURLSHE_OK;
  char *url;
  struct Tdata tdata;
  CURL *curl;
  CURLSH *share;
  struct curl_slist *headers;
  int i;
  struct userdata user;

  user.text = (char *)"Pigs in space";
  user.counter = 0;

  printf( "GLOBAL_INIT\n" );
  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* prepare share */
  printf( "SHARE_INIT\n" );
  if ((share = curl_share_init()) == NULL) {
    fprintf(stderr, "curl_share_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  if ( CURLSHE_OK == scode ) {
    printf( "CURLSHOPT_LOCKFUNC\n" );
    scode = curl_share_setopt( share, CURLSHOPT_LOCKFUNC, my_lock);
  }
  if ( CURLSHE_OK == scode ) {
    printf( "CURLSHOPT_UNLOCKFUNC\n" );
    scode = curl_share_setopt( share, CURLSHOPT_UNLOCKFUNC, my_unlock);
  }
  if ( CURLSHE_OK == scode ) {
    printf( "CURLSHOPT_USERDATA\n" );
    scode = curl_share_setopt( share, CURLSHOPT_USERDATA, &user);
  }
  if ( CURLSHE_OK == scode ) {
    printf( "CURL_LOCK_DATA_COOKIE\n" );
    scode = curl_share_setopt( share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
  }
  if ( CURLSHE_OK == scode ) {
    printf( "CURL_LOCK_DATA_DNS\n" );
    scode = curl_share_setopt( share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
  }

  if ( CURLSHE_OK != scode ) {
    fprintf(stderr, "curl_share_setopt() failed\n");
    curl_share_cleanup(share);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }


  res = 0;

  /* start treads */
  for (i=1; i<=THREADS; i++ ) {

    /* set thread data */
    tdata.url   = suburl( URL, i ); /* must be curl_free()d */
    tdata.share = share;

    /* simulate thread, direct call of "thread" function */
    printf( "*** run %d\n",i );
    fire( &tdata );

    curl_free( tdata.url );

  }


  /* fetch a another one and save cookies */
  printf( "*** run %d\n", i );
  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_share_cleanup(share);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  url = suburl( URL, i );
  headers = sethost( NULL );
  curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headers );
  curl_easy_setopt( curl, CURLOPT_URL,        url );
  printf( "CURLOPT_SHARE\n" );
  curl_easy_setopt( curl, CURLOPT_SHARE,      share );
  printf( "CURLOPT_COOKIEJAR\n" );
  curl_easy_setopt( curl, CURLOPT_COOKIEJAR,  JAR );

  printf( "PERFORM\n" );
  curl_easy_perform( curl );

  /* try to free share, expect to fail because share is in use*/
  printf( "try SHARE_CLEANUP...\n" );
  scode = curl_share_cleanup( share );
  if ( scode==CURLSHE_OK )
  {
    fprintf(stderr, "curl_share_cleanup succeed but error expected\n");
    share = NULL;
  } else {
    printf( "SHARE_CLEANUP failed, correct\n" );
  }

  /* clean up last handle */
  printf( "CLEANUP\n" );
  curl_easy_cleanup( curl );
  curl_slist_free_all( headers );

  curl_free(url);

  /* free share */
  printf( "SHARE_CLEANUP\n" );
  scode = curl_share_cleanup( share );
  if ( scode!=CURLSHE_OK )
    fprintf(stderr, "curl_share_cleanup failed, code errno %d\n",
            (int)scode);

  printf( "GLOBAL_CLEANUP\n" );
  curl_global_cleanup();

  return res;
}
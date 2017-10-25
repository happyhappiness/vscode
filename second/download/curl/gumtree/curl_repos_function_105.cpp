int test(char *URL)
{
  int res;
  CURLSHcode scode;
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
  curl_global_init( CURL_GLOBAL_ALL );

  /* prepare share */
  printf( "SHARE_INIT\n" );
  share = curl_share_init();
  scode = curl_share_setopt( share, CURLSHOPT_LOCKFUNC, lock);
  scode += curl_share_setopt( share, CURLSHOPT_UNLOCKFUNC, unlock);
  scode += curl_share_setopt( share, CURLSHOPT_USERDATA, &user);
  printf( "CURL_LOCK_DATA_COOKIE\n" );
  scode += curl_share_setopt( share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
  printf( "CURL_LOCK_DATA_DNS\n" );
  scode += curl_share_setopt( share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);

  if(scode) {
    curl_share_cleanup(share);
    return 2;
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
  curl = curl_easy_init();

  url = suburl( URL, i );
  headers = sethost( NULL );
  curl_easy_setopt( curl, CURLOPT_HTTPHEADER, (void*)headers );
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
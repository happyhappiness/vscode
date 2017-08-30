  return CURLE_OK;

}



/* true globals -- for curl_global_init() and curl_global_cleanup() */

static unsigned int  initialized;

static long          init_flags;


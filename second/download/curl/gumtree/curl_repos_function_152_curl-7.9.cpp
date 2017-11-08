CURLcode Curl_open(struct SessionHandle **curl)
{
  /* We don't yet support specifying the URL at this point */
  struct SessionHandle *data;
#ifdef HAVE_SIGACTION
  struct sigaction sigact;
#endif

  /* Very simple start-up: alloc the struct, init it with zeroes and return */
  data = (struct SessionHandle *)malloc(sizeof(struct SessionHandle));
  if(data) {
    memset(data, 0, sizeof(struct SessionHandle));

    /* We do some initial setup here, all those fields that can't be just 0 */

    data->state.headerbuff=(char*)malloc(HEADERSIZE);
    if(!data->state.headerbuff) {
      free(data); /* free the memory again */
      return CURLE_OUT_OF_MEMORY;
    }

    data->state.headersize=HEADERSIZE;

    data->set.out = stdout; /* default output to stdout */
    data->set.in  = stdin;  /* default input from stdin */
    data->set.err  = stderr;  /* default stderr to stderr */

    /* use fwrite as default function to store output */
    data->set.fwrite = (curl_write_callback)fwrite;

    /* use fread as default function to read input */
    data->set.fread = (curl_read_callback)fread;

    /* set the default passwd function */
    data->set.fpasswd = my_getpass;

    data->set.infilesize = -1; /* we don't know any size */

    data->state.current_speed = -1; /* init to negative == impossible */

    data->set.httpreq = HTTPREQ_GET; /* Default HTTP request */

    /* make libcurl quiet by default: */
    data->set.hide_progress = TRUE;  /* CURLOPT_NOPROGRESS changes these */
    data->progress.flags |= PGRS_HIDE;

    /* Set the default size of the SSL session ID cache */
    data->set.ssl.numsessions = 5;

    /* create an array with connection data struct pointers */
    data->state.numconnects = 5; /* hard-coded right now */
    data->state.connects = (struct connectdata **)
      malloc(sizeof(struct connectdata *) * data->state.numconnects);

    if(!data->state.connects) {
      free(data);
      return CURLE_OUT_OF_MEMORY;
    }

    memset(data->state.connects, 0,
           sizeof(struct connectdata *)*data->state.numconnects);

    *curl = data;

    /*************************************************************
     * Set signal handler
     *************************************************************/
#ifdef HAVE_SIGACTION
    sigaction(SIGALRM, NULL, &sigact);
    sigact.sa_handler = alarmfunc;
#ifdef SA_RESTART
    /* HPUX doesn't have SA_RESTART but defaults to that behaviour! */
    sigact.sa_flags &= ~SA_RESTART;
#endif
    sigaction(SIGALRM, &sigact, NULL);
#else
    /* no sigaction(), revert to the much lamer signal() */
#ifdef HAVE_SIGNAL
    signal(SIGALRM, alarmfunc);
#endif

#endif

    return CURLE_OK;
  }

  /* this is a very serious error */
  return CURLE_OUT_OF_MEMORY;
}
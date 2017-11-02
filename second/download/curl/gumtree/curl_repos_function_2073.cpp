int GetOrSetUpData(int id, libdata_t **appData,
                   libthreaddata_t **threadData )
{
  int                 err;
  libdata_t           *app_data;
  libthreaddata_t *thread_data;
  NXKey_t             key;
  NX_LOCK_INFO_ALLOC(liblock, "Application Data Lock", 0);

  err         = 0;
  thread_data = (libthreaddata_t *) NULL;

  /*
   * Attempt to get our data for the application calling us. This is where we
   * store whatever application-specific information we need to carry in
   * support of calling applications.
   */
  app_data = (libdata_t *) get_app_data(id);

  if(!app_data) {
    /*
     * This application hasn't called us before; set up application AND
     * per-thread data. Of course, just in case a thread from this same
     * application is calling us simultaneously, we better lock our application
     * data-creation mutex. We also need to recheck for data after we acquire
     * the lock because WE might be that other thread that was too late to
     * create the data and the first thread in will have created it.
     */
    NXLock(gLibLock);

    if(!(app_data = (libdata_t *) get_app_data(id))) {
      app_data = malloc(sizeof(libdata_t));

      if(app_data) {
        memset(app_data, 0, sizeof(libdata_t));

        app_data->tenbytes = malloc(10);
        app_data->lock     = NXMutexAlloc(0, 0, &liblock);

        if(!app_data->tenbytes || !app_data->lock) {
          if(app_data->lock)
            NXMutexFree(app_data->lock);

          free(app_data);
          app_data = (libdata_t *) NULL;
          err      = ENOMEM;
        }

        if(app_data) {
          /*
           * Here we burn in the application data that we were trying to get
           * by calling get_app_data(). Next time we call the first function,
           * we'll get this data we're just now setting. We also go on here to
           * establish the per-thread data for the calling thread, something
           * we'll have to do on each application thread the first time
           * it calls us.
           */
          err = set_app_data(gLibId, app_data);

          if(err) {
            free(app_data);
            app_data = (libdata_t *) NULL;
            err      = ENOMEM;
          }
          else {
            /* create key for thread-specific data... */
            err = NXKeyCreate(DisposeThreadData, (void *) NULL, &key);

            if(err)                /* (no more keys left?) */
              key = -1;

            app_data->perthreadkey = key;
          }
        }
      }
    }

    NXUnlock(gLibLock);
  }

  if(app_data) {
    key = app_data->perthreadkey;

    if(key != -1 /* couldn't create a key? no thread data */
        && !(err = NXKeyGetValue(key, (void **) &thread_data))
        && !thread_data) {
      /*
       * Allocate the per-thread data for the calling thread. Regardless of
       * whether there was already application data or not, this may be the
       * first call by a new thread. The fact that we allocation 20 bytes on
       * a pointer is not very important, this just helps to demonstrate that
       * we can have arbitrarily complex per-thread data.
       */
      thread_data = malloc(sizeof(libthreaddata_t));

      if(thread_data) {
        thread_data->_errno      = 0;
        thread_data->twentybytes = malloc(20);

        if(!thread_data->twentybytes) {
          free(thread_data);
          thread_data = (libthreaddata_t *) NULL;
          err         = ENOMEM;
        }

        if((err = NXKeySetValue(key, thread_data))) {
          free(thread_data->twentybytes);
          free(thread_data);
          thread_data = (libthreaddata_t *) NULL;
        }
      }
    }
  }

  if(appData)
    *appData = app_data;

  if(threadData)
    *threadData = thread_data;

  return err;
}
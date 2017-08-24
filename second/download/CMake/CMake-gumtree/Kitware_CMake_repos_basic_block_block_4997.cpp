{
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

        err = NXKeySetValue(key, thread_data);
        if(err) {
          free(thread_data->twentybytes);
          free(thread_data);
          thread_data = (libthreaddata_t *) NULL;
        }
      }
    }
  }
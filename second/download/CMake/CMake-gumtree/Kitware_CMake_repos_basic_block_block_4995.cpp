{
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
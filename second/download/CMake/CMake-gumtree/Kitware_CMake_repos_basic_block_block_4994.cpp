{
          free(thread_data);
          thread_data = (libthreaddata_t *) NULL;
          err         = ENOMEM;
        }
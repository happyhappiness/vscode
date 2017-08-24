{
          free(thread_data->twentybytes);
          free(thread_data);
          thread_data = (libthreaddata_t *) NULL;
        }
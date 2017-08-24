{
          if(app_data->lock)
            NXMutexFree(app_data->lock);

          free(app_data);
          app_data = (libdata_t *) NULL;
          err      = ENOMEM;
        }
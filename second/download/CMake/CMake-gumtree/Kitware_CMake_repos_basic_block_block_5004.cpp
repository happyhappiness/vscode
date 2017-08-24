f(app_data) {
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
{
        infof(data, "Unwillingly accepted illegal URL using %d slash%s!\n",
              s, s>1?"es":"");

        if(data->change.url_alloc)
          free(data->change.url);
        /* repair the URL to use two slashes */
        data->change.url = aprintf("%s://%s%s",
                                   protobuf, conn->host.name, path);
        if(!data->change.url)
          return CURLE_OUT_OF_MEMORY;
        data->change.url_alloc = TRUE;
      }
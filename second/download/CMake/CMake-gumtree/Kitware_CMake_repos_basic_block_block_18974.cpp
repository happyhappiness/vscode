{
    /* Create new FSEventStream */
    cf_paths = pCFArrayCreate(NULL, (const void**) paths, path_count, NULL);
    if (cf_paths == NULL) {
      err = -ENOMEM;
      goto final;
    }
    err = uv__fsevents_create_stream(handle->loop, cf_paths);
  }
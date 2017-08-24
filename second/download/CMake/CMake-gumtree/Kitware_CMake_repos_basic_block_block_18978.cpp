(path_count != 0) {
    paths = uv__malloc(sizeof(*paths) * path_count);
    if (paths == NULL) {
      uv_mutex_unlock(&state->fsevent_mutex);
      goto final;
    }

    q = &state->fsevent_handles;
    for (; i < path_count; i++) {
      q = QUEUE_NEXT(q);
      assert(q != &state->fsevent_handles);
      curr = QUEUE_DATA(q, uv_fs_event_t, cf_member);

      assert(curr->realpath != NULL);
      paths[i] =
          pCFStringCreateWithFileSystemRepresentation(NULL, curr->realpath);
      if (paths[i] == NULL) {
        uv_mutex_unlock(&state->fsevent_mutex);
        goto final;
      }
    }
  }
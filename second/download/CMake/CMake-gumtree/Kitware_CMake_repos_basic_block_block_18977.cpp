{
  uv__cf_loop_state_t* state;
  QUEUE* q;
  uv_fs_event_t* curr;
  CFArrayRef cf_paths;
  CFStringRef* paths;
  unsigned int i;
  int err;
  unsigned int path_count;

  state = handle->loop->cf_state;
  paths = NULL;
  cf_paths = NULL;
  err = 0;
  /* NOTE: `i` is used in deallocation loop below */
  i = 0;

  /* Optimization to prevent O(n^2) time spent when starting to watch
   * many files simultaneously
   */
  uv_mutex_lock(&state->fsevent_mutex);
  if (state->fsevent_need_reschedule == 0) {
    uv_mutex_unlock(&state->fsevent_mutex);
    goto final;
  }
  state->fsevent_need_reschedule = 0;
  uv_mutex_unlock(&state->fsevent_mutex);

  /* Destroy previous FSEventStream */
  uv__fsevents_destroy_stream(handle->loop);

  /* Any failure below will be a memory failure */
  err = -ENOMEM;

  /* Create list of all watched paths */
  uv_mutex_lock(&state->fsevent_mutex);
  path_count = state->fsevent_handle_count;
  if (path_count != 0) {
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
  uv_mutex_unlock(&state->fsevent_mutex);
  err = 0;

  if (path_count != 0) {
    /* Create new FSEventStream */
    cf_paths = pCFArrayCreate(NULL, (const void**) paths, path_count, NULL);
    if (cf_paths == NULL) {
      err = -ENOMEM;
      goto final;
    }
    err = uv__fsevents_create_stream(handle->loop, cf_paths);
  }

final:
  /* Deallocate all paths in case of failure */
  if (err != 0) {
    if (cf_paths == NULL) {
      while (i != 0)
        pCFRelease(paths[--i]);
      uv__free(paths);
    } else {
      /* CFArray takes ownership of both strings and original C-array */
      pCFRelease(cf_paths);
    }

    /* Broadcast error to all handles */
    uv_mutex_lock(&state->fsevent_mutex);
    QUEUE_FOREACH(q, &state->fsevent_handles) {
      curr = QUEUE_DATA(q, uv_fs_event_t, cf_member);
      uv__fsevents_push_event(curr, NULL, err);
    }
    uv_mutex_unlock(&state->fsevent_mutex);
  }

  /*
   * Main thread will block until the removal of handle from the list,
   * we must tell it when we're ready.
   *
   * NOTE: This is coupled with `uv_sem_wait()` in `uv__fsevents_close`
   */
  if (type == kUVCFLoopSignalClosing)
    uv_sem_post(&state->fsevent_sem);
}
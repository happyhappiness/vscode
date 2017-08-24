{
  struct watcher_list* w;
  int events;
  int err;
  int wd;

  if (uv__is_active(handle))
    return -EINVAL;

  err = init_inotify(handle->loop);
  if (err)
    return err;

  events = UV__IN_ATTRIB
         | UV__IN_CREATE
         | UV__IN_MODIFY
         | UV__IN_DELETE
         | UV__IN_DELETE_SELF
         | UV__IN_MOVE_SELF
         | UV__IN_MOVED_FROM
         | UV__IN_MOVED_TO;

  wd = uv__inotify_add_watch(handle->loop->inotify_fd, path, events);
  if (wd == -1)
    return -errno;

  w = find_watcher(handle->loop, wd);
  if (w)
    goto no_insert;

  w = uv__malloc(sizeof(*w) + strlen(path) + 1);
  if (w == NULL)
    return -ENOMEM;

  w->wd = wd;
  w->path = strcpy((char*)(w + 1), path);
  QUEUE_INIT(&w->watchers);
  w->iterating = 0;
  RB_INSERT(watcher_root, CAST(&handle->loop->inotify_watchers), w);

no_insert:
  uv__handle_start(handle);
  QUEUE_INSERT_TAIL(&w->watchers, &handle->watchers);
  handle->path = w->path;
  handle->cb = cb;
  handle->wd = wd;

  return 0;
}
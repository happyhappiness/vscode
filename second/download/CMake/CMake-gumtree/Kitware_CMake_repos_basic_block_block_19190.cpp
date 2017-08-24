{
    /* No watchers left for this path. Clean up. */
    RB_REMOVE(watcher_root, CAST(&loop->inotify_watchers), w);
    uv__inotify_rm_watch(loop->inotify_fd, w->wd);
    uv__free(w);
  }
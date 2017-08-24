{
    /* stop the watcher before we blow away its fileno */
    uv__io_stop(loop, &loop->fs_event_watcher, POLLIN);
  }
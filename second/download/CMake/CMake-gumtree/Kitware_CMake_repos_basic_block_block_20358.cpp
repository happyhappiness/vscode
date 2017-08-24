{
    handle = loop->endgame_handles;
    loop->endgame_handles = handle->endgame_next;

    handle->flags &= ~UV_HANDLE_ENDGAME_QUEUED;

    switch (handle->type) {
      case UV_TCP:
        uv_tcp_endgame(loop, (uv_tcp_t*) handle);
        break;

      case UV_NAMED_PIPE:
        uv_pipe_endgame(loop, (uv_pipe_t*) handle);
        break;

      case UV_TTY:
        uv_tty_endgame(loop, (uv_tty_t*) handle);
        break;

      case UV_UDP:
        uv_udp_endgame(loop, (uv_udp_t*) handle);
        break;

      case UV_POLL:
        uv_poll_endgame(loop, (uv_poll_t*) handle);
        break;

      case UV_TIMER:
        uv_timer_endgame(loop, (uv_timer_t*) handle);
        break;

      case UV_PREPARE:
      case UV_CHECK:
      case UV_IDLE:
        uv_loop_watcher_endgame(loop, handle);
        break;

      case UV_ASYNC:
        uv_async_endgame(loop, (uv_async_t*) handle);
        break;

      case UV_SIGNAL:
        uv_signal_endgame(loop, (uv_signal_t*) handle);
        break;

      case UV_PROCESS:
        uv_process_endgame(loop, (uv_process_t*) handle);
        break;

      case UV_FS_EVENT:
        uv_fs_event_endgame(loop, (uv_fs_event_t*) handle);
        break;

      case UV_FS_POLL:
        uv__fs_poll_endgame(loop, (uv_fs_poll_t*) handle);
        break;

      default:
        assert(0);
        break;
    }
  }
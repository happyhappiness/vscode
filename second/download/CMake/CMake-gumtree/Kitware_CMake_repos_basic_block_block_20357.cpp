{
    handle->flags |= UV_HANDLE_ENDGAME_QUEUED;

    handle->endgame_next = loop->endgame_handles;
    loop->endgame_handles = handle;
  }
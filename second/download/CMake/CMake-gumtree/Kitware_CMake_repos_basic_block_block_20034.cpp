{
    loop = uv__loops[i];
    assert(loop);
    if (loop->iocp != INVALID_HANDLE_VALUE)
      PostQueuedCompletionStatus(loop->iocp, 0, 0, NULL);
  }
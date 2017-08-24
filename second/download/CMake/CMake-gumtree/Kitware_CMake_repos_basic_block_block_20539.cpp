{
  uv_pipe_t* pipe = (uv_pipe_t*) timer->data;
  uv_loop_t* loop = timer->loop;

  assert(pipe->type == UV_NAMED_PIPE);

  /* This should always be true, since we start the timer only */
  /* in uv_pipe_queue_read after successfully calling ReadFile, */
  /* or in uv_process_pipe_shutdown_req if a read is pending, */
  /* and we always immediately stop the timer in */
  /* uv_process_pipe_read_req. */
  assert(pipe->flags & UV_HANDLE_READ_PENDING);

  /* If there are many packets coming off the iocp then the timer callback */
  /* may be called before the read request is coming off the queue. */
  /* Therefore we check here if the read request has completed but will */
  /* be processed later. */
  if ((pipe->flags & UV_HANDLE_READ_PENDING) &&
      HasOverlappedIoCompleted(&pipe->read_req.u.io.overlapped)) {
    return;
  }

  /* Force both ends off the pipe. */
  close_pipe(pipe);

  /* Stop reading, so the pending read that is going to fail will */
  /* not be reported to the user. */
  uv_read_stop((uv_stream_t*) pipe);

  /* Report the eof and update flags. This will get reported even if the */
  /* user stopped reading in the meantime. TODO: is that okay? */
  uv_pipe_read_eof(loop, pipe, uv_null_buf_);
}
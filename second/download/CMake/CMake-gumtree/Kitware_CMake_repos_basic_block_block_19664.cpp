(send_handle) {
    if (stream->type != UV_NAMED_PIPE || !((uv_pipe_t*)stream)->ipc)
      return -EINVAL;

    /* XXX We abuse uv_write2() to send over UDP handles to child processes.
     * Don't call uv__stream_fd() on those handles, it's a macro that on OS X
     * evaluates to a function that operates on a uv_stream_t with a couple of
     * OS X specific fields. On other Unices it does (handle)->io_watcher.fd,
     * which works but only by accident.
     */
    if (uv__handle_fd((uv_handle_t*) send_handle) < 0)
      return -EBADF;

#if defined(__CYGWIN__) || defined(__MSYS__)
    /* Cygwin recvmsg always sets msg_controllen to zero, so we cannot send it.
       See https://github.com/mirror/newlib-cygwin/blob/86fc4bf0/winsup/cygwin/fhandler_socket.cc#L1736-L1743 */
    return -ENOSYS;
#endif
  }
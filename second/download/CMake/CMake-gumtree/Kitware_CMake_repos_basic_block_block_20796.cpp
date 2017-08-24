(!(stream->flags & UV_HANDLE_WRITABLE))
    return UV_EPIPE;
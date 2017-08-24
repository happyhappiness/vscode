(nread < buflen) {
        stream->flags |= UV_STREAM_READ_PARTIAL;
        return;
      }
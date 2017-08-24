(QUEUE_EMPTY(&stream->write_queue))
      uv__drain(stream)
{
      ACCESS_ONCE(int, s->events) = events;

      uv_async_send(&s->async);
      uv_sem_wait(&s->async_sem);

      /* Should be processed at this stage */
      assert((s->events == 0) || (stream->flags & UV_CLOSING));
    }
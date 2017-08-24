{
        q = QUEUE_HEAD(&queue);
        h = QUEUE_DATA(q, uv_fs_event_t, watchers);

        QUEUE_REMOVE(q);
        QUEUE_INSERT_TAIL(&w->watchers, q);

        h->cb(h, path, events, 0);
      }
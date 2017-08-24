{
        q = QUEUE_HEAD(&queue);
        handle = QUEUE_DATA(q, uv_fs_event_t, watchers);
        /* It's critical to keep a copy of path here, because it
         * will be set to NULL by stop() and then deallocated by
         * maybe_free_watcher_list
         */
        tmp_path = uv__strdup(handle->path);
        assert(tmp_path != NULL);
        QUEUE_REMOVE(q);
        QUEUE_INSERT_TAIL(&watcher_list->watchers, q);
        uv_fs_event_stop(handle);

        QUEUE_INSERT_TAIL(&tmp_watcher_list.watchers, &handle->watchers);
        handle->path = tmp_path;
      }
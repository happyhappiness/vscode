(i = 0; i < numEvents; i++) {
      /* Ignore system events */
      if (eventFlags[i] & kFSEventsSystem)
        continue;

      path = paths[i];
      len = strlen(path);

      /* Filter out paths that are outside handle's request */
      if (strncmp(path, handle->realpath, handle->realpath_len) != 0)
        continue;

      if (handle->realpath_len > 1 || *handle->realpath != '/') {
        path += handle->realpath_len;
        len -= handle->realpath_len;

        /* Skip forward slash */
        if (*path != '\0') {
          path++;
          len--;
        }
      }

#ifdef MAC_OS_X_VERSION_10_7
      /* Ignore events with path equal to directory itself */
      if (len == 0)
        continue;
#endif /* MAC_OS_X_VERSION_10_7 */

      /* Do not emit events from subdirectories (without option set) */
      if ((handle->cf_flags & UV_FS_EVENT_RECURSIVE) == 0 && *path != 0) {
        pos = strchr(path + 1, '/');
        if (pos != NULL)
          continue;
      }

#ifndef MAC_OS_X_VERSION_10_7
      path = "";
      len = 0;
#endif /* MAC_OS_X_VERSION_10_7 */

      event = uv__malloc(sizeof(*event) + len);
      if (event == NULL)
        break;

      memset(event, 0, sizeof(*event));
      memcpy(event->path, path, len + 1);

      if ((eventFlags[i] & kFSEventsModified) != 0 &&
          (eventFlags[i] & kFSEventsRenamed) == 0)
        event->events = UV_CHANGE;
      else
        event->events = UV_RENAME;

      QUEUE_INSERT_TAIL(&head, &event->member);
    }
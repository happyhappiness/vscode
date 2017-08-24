(uv__path_is_a_directory(handle->path) == 0) { /* Directory */
      if (evp_rc == AHAFS_MODDIR_UNMOUNT || evp_rc == AHAFS_MODDIR_REMOVE_SELF) {
        /* The directory is no longer available for monitoring */
        *events = UV_RENAME;
        handle->dir_filename = NULL;
      } else {
        /* A file was added/removed inside the directory */
        *events = UV_CHANGE;

        /* Get the EVPROD_INFO */
        if (uv__skip_lines(&p, 1) != 1)
          return -1;

        /* Scan out the name of the file that triggered the event*/
        if (sscanf(p, "BEGIN_EVPROD_INFO\n%sEND_EVPROD_INFO", filename) == 1) {
          handle->dir_filename = uv__strdup((const char*)&filename);
        } else
          return -1;
        }
    } else { /* Regular File */
      if (evp_rc == AHAFS_MODFILE_RENAME)
        *events = UV_RENAME;
      else
        *events = UV_CHANGE;
    }
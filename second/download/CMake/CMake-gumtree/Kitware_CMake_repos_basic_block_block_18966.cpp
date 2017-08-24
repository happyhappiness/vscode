{
        path += handle->realpath_len;
        len -= handle->realpath_len;

        /* Skip forward slash */
        if (*path != '\0') {
          path++;
          len--;
        }
      }
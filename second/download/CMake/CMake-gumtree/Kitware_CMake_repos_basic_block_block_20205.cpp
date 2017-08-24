{
        size_t new_dirents_size =
            dirents_size == 0 ? dirents_initial_size : dirents_size << 1;
        uv__dirent_t** new_dirents =
            uv__realloc(dirents, new_dirents_size * sizeof *dirents);

        if (new_dirents == NULL)
          goto out_of_memory_error;

        dirents_size = new_dirents_size;
        dirents = new_dirents;
      }
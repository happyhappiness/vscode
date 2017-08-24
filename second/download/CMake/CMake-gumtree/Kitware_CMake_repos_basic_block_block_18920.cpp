(nread == -1) {
      if (use_pread && nsent == 0 && (errno == EIO || errno == ESPIPE)) {
        use_pread = 0;
        continue;
      }

      if (nsent == 0)
        nsent = -1;

      goto out;
    }
(pollset_ctl(loop->backend_fd, &pc, 1)) {
        if (errno != EINVAL) {
          assert(0 && "Failed to add file descriptor (pc.fd) to pollset");
          abort();
        }
        /* Check if the fd is already in the pollset */
        pqry.fd = pc.fd;
        rc = pollset_query(loop->backend_fd, &pqry);
        switch (rc) {
        case -1:
          assert(0 && "Failed to query pollset for file descriptor");
          abort();
        case 0:
          assert(0 && "Pollset does not contain file descriptor");
          abort();
        }
        /* If we got here then the pollset already contained the file descriptor even though
         * we didn't think it should. This probably shouldn't happen, but we can continue. */
        add_failed = 1;
      }
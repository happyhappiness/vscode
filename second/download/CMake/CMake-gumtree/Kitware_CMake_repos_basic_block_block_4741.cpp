f((bitmap & GETSOCK_WRITESOCK(i)) && VALID_SOCK((sockbunch[i]))) {
        FD_SET(sockbunch[i], write_fd_set);
        s = sockbunch[i];
      }
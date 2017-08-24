(err == EINVAL && sigprocmask(how, set, oset) == 0) {
        workaround = 1;
        return 0;
      } else {
        return -1;
      }
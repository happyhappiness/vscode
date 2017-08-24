(err == WSAEADDRINUSE) {
      /* Some errors are not to be reported until connect() or listen() */
      handle->delayed_error = err;
    } else {
      return err;
    }
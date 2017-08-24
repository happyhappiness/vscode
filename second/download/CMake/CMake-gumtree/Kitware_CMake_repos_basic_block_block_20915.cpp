{
        /*
         * Turn WSAECONNABORTED into UV_ECONNRESET to be consistent with Unix.
         */
        err = WSAECONNRESET;
      }
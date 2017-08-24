{
      const PRErrorCode err = PR_GetError();
      if(!display_error(conn, err, key_file)) {
        const char *err_name = nss_error_to_name(err);
        failf(data, "unable to load client key: %d (%s)", err, err_name);
      }

      return result;
    }
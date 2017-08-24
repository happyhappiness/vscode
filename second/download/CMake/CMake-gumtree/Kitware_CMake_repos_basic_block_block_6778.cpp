f(result) {
      const PRErrorCode err = PR_GetError();
      if(!display_error(conn, err, cert_file)) {
        const char *err_name = nss_error_to_name(err);
        failf(data, "unable to load client cert: %d (%s)", err, err_name);
      }

      return result;
    }
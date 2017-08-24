{
        const char *err_name = nss_error_to_name(err);
        failf(data, "unable to load client cert: %d (%s)", err, err_name);
      }
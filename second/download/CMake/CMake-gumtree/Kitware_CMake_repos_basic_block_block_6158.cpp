{
        failf(data, "Couldn't resolve host '%s'", connhost->dispname);
        result =  CURLE_COULDNT_RESOLVE_HOST;
        /* don't return yet, we need to clean up the timeout first */
      }
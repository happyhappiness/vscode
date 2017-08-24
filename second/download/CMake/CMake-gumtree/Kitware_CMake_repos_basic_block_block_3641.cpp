f(!conn->async.dns) {
      failf(data, "Could not resolve: %s (%s)",
            conn->async.hostname, ares_strerror(conn->async.status));
      result = conn->bits.proxy?CURLE_COULDNT_RESOLVE_PROXY:
        CURLE_COULDNT_RESOLVE_HOST;
    }
    else
      *dns = conn->async.dns
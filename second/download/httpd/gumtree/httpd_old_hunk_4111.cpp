    }

    /* Step 3: Read records from the back end server and handle them. */
    rv = dispatch(conn, conf, r, temp_pool, request_id,
                  &err, &bad_request, &has_responded);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01075)
                      "Error dispatching request to %s: %s%s%s",
                      server_portstr,
                      err ? "(" : "",
                      err ? err : "",
                      err ? ")" : "");

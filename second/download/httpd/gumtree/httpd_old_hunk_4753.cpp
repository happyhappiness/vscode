                      "data to read (max %" APR_SIZE_T_FMT
                      " at %" APR_SIZE_T_FMT ")", bufsiz, msg->pos);

        status = apr_brigade_flatten(input_brigade, buff, &bufsiz);
        if (status != APR_SUCCESS) {
            /* We had a failure: Close connection to backend */
            conn->close++;
            apr_brigade_destroy(input_brigade);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(00874)
                          "apr_brigade_flatten");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_brigade_cleanup(input_brigade);

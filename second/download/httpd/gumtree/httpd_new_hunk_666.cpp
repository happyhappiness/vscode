            recursive_error = HTTP_INTERNAL_SERVER_ERROR;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Invalid error redirection directive: %s",
                        custom_response);
        }
    }
    ap_send_error_response(r_1st_err, recursive_error);
}

static void check_pipeline_flush(request_rec *r)
{
    conn_rec *c = r->connection;
    /* ### if would be nice if we could PEEK without a brigade. that would

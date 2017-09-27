             * some modules.
             * Content-Length can't be unset here because that would break
             * being able to read the request body.
             * Processing of chunked request bodies is not impacted by this
             * filter since the the length was not declared anyway.
             */
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, f->r,
                          "Request body length may change, resulting in "
                          "misprocessing by some modules or scripts");
        }
    }

    if (ctx->noop) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

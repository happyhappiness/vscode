            expr = tag_val;

#ifdef DEBUG_INCLUDE

            ap_rvputs(r, "**** if expr=\"", expr, "\"\n", NULL);

#endif

        }

        else {

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                        "unknown parameter \"%s\" to tag if in %s",

                        tag, r->filename);

            ap_rputs(error, r);

        }

    }

}


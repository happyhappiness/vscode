            ctx->dc = dc;
            ctx->noop = 1;
        }
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, f->r,
                     "xlate_out_filter() - "
                     "charset_source: %s charset_default: %s",
                     dc && dc->charset_source ? dc->charset_source : "(none)",
                     dc && dc->charset_default ? dc->charset_default : "(none)");
    }


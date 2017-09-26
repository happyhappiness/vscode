                     dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
    }

    if (ctx->noop) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }


        real = proxy_interpolate(r, ent->real);
    }
    else {
        fake = ent->fake;
        real = ent->real;
    }
    if (ent->regex) {
        if (!ap_regexec(ent->regex, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
            if ((real[0] == '!') && (real[1] == '\0')) {
                return DECLINED;
            }
            /* test that we haven't reduced the URI */
            if (nocanon && ap_regexec(ent->regex, r->unparsed_uri,
                    AP_MAX_REG_MATCH, reg1, 0)) {
                mismatch = 1;

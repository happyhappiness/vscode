    }
    else {
        len = alias_match(r->uri, fake);

        if (len != 0) {
            if ((real[0] == '!') && (real[1] == '\0')) {
                return DECLINED;
            }
            if (nocanon && len != alias_match(r->unparsed_uri, ent->fake)) {
                mismatch = 1;
                use_uri = r->uri;
            }

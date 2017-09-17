        if (!(tag_val = get_tag(r->pool, in, tag, sizeof(tag), 1))) {
            return 1;
        }
        if (!strcmp(tag, "cmd")) {
            parse_string(r, tag_val, parsed_string, sizeof(parsed_string), 1);
            if (include_cmd(parsed_string, r) == -1) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "execution failure for parameter \"%s\" "
                            "to tag exec in file %s",
                            tag, r->filename);
                ap_rputs(error, r);
            }
            /* just in case some stooge changed directories */

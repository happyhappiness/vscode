    char parsed_string[MAX_STRING_LEN];

    char *tag_val;

    SV *sub = Nullsv;

    AV *av = newAV();



    if (!(ap_allow_options(r) & OPT_INCLUDES)) {

        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                    "httpd: #perl SSI disallowed by IncludesNoExec in %s",

                    r->filename);

        return DECLINED;

    }

    while (1) {

        if (!(tag_val = get_tag(r->pool, in, tag, sizeof(tag), 1))) {


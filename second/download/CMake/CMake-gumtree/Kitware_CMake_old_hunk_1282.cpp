    path = archive_entry_pathname(entry_main);

    path_w = archive_entry_pathname_w(entry_main);

    if (path != NULL && path_w == NULL) {

        archive_set_error(&a->archive, EILSEQ,

            "Can't translate pathname '%s' to UTF-8", path);

        ret = ARCHIVE_WARN;

        hdrcharset = "BINARY";

    }

    uname = archive_entry_uname(entry_main);

    uname_w = archive_entry_uname_w(entry_main);

    if (uname != NULL && uname_w == NULL) {

        archive_set_error(&a->archive, EILSEQ,

            "Can't translate uname '%s' to UTF-8", uname);

        ret = ARCHIVE_WARN;

        hdrcharset = "BINARY";

    }

    gname = archive_entry_gname(entry_main);

    gname_w = archive_entry_gname_w(entry_main);

    if (gname != NULL && gname_w == NULL) {

        archive_set_error(&a->archive, EILSEQ,

            "Can't translate gname '%s' to UTF-8", gname);

        ret = ARCHIVE_WARN;

        hdrcharset = "BINARY";


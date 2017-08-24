{
        archive_set_error(&a->archive, EILSEQ,
            "Can't translate gname '%s' to UTF-8", gname);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }
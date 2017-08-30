{
        archive_set_error(&a->archive, EILSEQ,
            "Can't translate linkpath '%s' to UTF-8", linkpath);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }
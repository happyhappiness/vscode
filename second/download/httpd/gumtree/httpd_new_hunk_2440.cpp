        }
    }
    ap_cfg_closefile(f);

    to_charset = derive_codepage_from_lang (p, "utf-8");
    if (to_charset == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s, APLOGNO(01752)
                     "could not find the UTF-8 charset in the file %s.",
                     charset_confname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    return OK;

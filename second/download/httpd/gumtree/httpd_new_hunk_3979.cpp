    case EES_DOWNSTREAM:
        msg = APLOGNO(02197) "xlate filter - an error occurred in a lower filter";
        break;
    default:
        msg = APLOGNO(02198) "xlate filter - returning error";
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(02997) "%s", msg);
}

/* chk_filter_chain() is called once per filter instance; it tries to
 * determine if the current filter instance should be disabled because
 * its translation is incompatible with the translation of an existing
 * instance of the translate filter

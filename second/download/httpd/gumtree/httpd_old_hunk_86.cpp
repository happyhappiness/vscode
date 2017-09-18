    case EES_DOWNSTREAM:
        msg = "xlate filter - an error occurred in a lower filter";
        break;
    default:
        msg = "xlate filter - returning error";
    }
    ap_log_rerror(APLOG_MARK, flags, rv, f->r,
                  "%s", msg);
}

/* chk_filter_chain() is called once per filter instance; it tries to
 * determine if the current filter instance should be disabled because
 * its translation is incompatible with the translation of an existing

	}
	return;

    case DATE:
    case BEDATE:
    case LEDATE:
        apr_ctime(time_str, apr_time_from_sec(*(time_t *)&p->l));
        pp = time_str;
	(void) magic_rsl_printf(r, m->desc, pp);
	return;
    default:
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		    MODNAME ": invalid m->type (%d) in mprint().",

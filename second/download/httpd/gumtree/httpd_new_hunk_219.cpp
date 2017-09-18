    case LEDATE:
        apr_ctime(time_str, APR_USEC_PER_SEC * (apr_time_t)*(time_t *)&p->l);
        pp = time_str;
	(void) magic_rsl_printf(r, m->desc, pp);
	return;
    default:
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		    MODNAME ": invalid m->type (%d) in mprint().",
		    m->type);
	return;
    }

    v = signextend(r->server, m, v) & m->mask;

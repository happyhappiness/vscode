	pp = ctime((time_t *) & p->l);

	if ((rt = strchr(pp, '\n')) != NULL)

	    *rt = '\0';

	(void) magic_rsl_printf(r, m->desc, pp);

	return;

    default:

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,

		    MODNAME ": invalid m->type (%d) in mprint().",

		    m->type);

	return;

    }



    v = signextend(r->server, m, v) & m->mask;


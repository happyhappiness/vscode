    case LELONG:
    case LEDATE:
	p->l = (long)
	    ((p->hl[3] << 24) | (p->hl[2] << 16) | (p->hl[1] << 8) | (p->hl[0]));
	return 1;
    default:
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, r,
		    MODNAME ": invalid type %d in mconvert().", m->type);
	return 0;
    }
}



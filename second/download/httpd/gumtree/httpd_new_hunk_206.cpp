		m->in.type = SHORT;
		break;
	    case 'b':
		m->in.type = BYTE;
		break;
	    default:
		ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
			MODNAME ": indirect offset type %c invalid", *l);
		break;
	    }
	    l++;
	}
	s = l;

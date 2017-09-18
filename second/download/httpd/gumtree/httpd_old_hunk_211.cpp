	(void) magic_rsl_puts(r, MIME_BINARY_UNKNOWN);
	return DONE;
    case APR_LNK:
	/* We used stat(), the only possible reason for this is that the
	 * symlink is broken.
	 */
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, r,
		    MODNAME ": broken symlink (%s)", fn);
	return HTTP_INTERNAL_SERVER_ERROR;
    case APR_SOCK:
	magic_rsl_puts(r, MIME_BINARY_UNKNOWN);
	return DONE;
    case APR_REG:
	break;
    default:
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, 0, r,
		      MODNAME ": invalid file type %d.", r->finfo.filetype);
	return HTTP_INTERNAL_SERVER_ERROR;
    }

    /*
     * regular file, check next possibility

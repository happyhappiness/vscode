	return DONE;

#endif

#endif

    case S_IFREG:

	break;

    default:

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,

		    MODNAME ": invalid mode 0%o.", (unsigned int)r->finfo.st_mode);

	return HTTP_INTERNAL_SERVER_ERROR;

    }



    /*

     * regular file, check next possibility


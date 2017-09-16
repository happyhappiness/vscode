#endif

            if (*conditional_status) {

                *printing = 0;

                return (0);

            }

	    if (expr == NULL) {

		ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

			    "missing expr in elif statement: %s",

			    r->filename);

		ap_rputs(error, r);

		return 1;

	    }

            *printing = *conditional_status = parse_expr(r, expr, error);


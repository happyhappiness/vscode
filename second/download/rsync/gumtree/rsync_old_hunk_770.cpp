			 * close the socket. */
			return RERR_STARTCLIENT;
		} else {
			rprintf(FINFO,"%s\n", line);
		}
	}
	kludge_around_eof = False;

	for (i = 0; i < sargc; i++) {
		io_printf(f_out, "%s\n", sargs[i]);
	}
	io_printf(f_out, "\n");


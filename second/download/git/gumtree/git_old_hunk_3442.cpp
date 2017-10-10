
	need_in = async->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			if (async->out > 0)
				close(async->out);
			return error("cannot create pipe: %s", strerror(errno));
		}
		async->in = fdin[1];
	}

	need_out = async->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			if (need_in)
				close_pair(fdin);
			else if (async->in)
				close(async->in);
			return error("cannot create pipe: %s", strerror(errno));
		}
		async->out = fdout[0];
	}

	if (need_in)
		proc_in = fdin[0];

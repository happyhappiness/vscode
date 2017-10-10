	if (!enabled && !service->overridable) {
		logerror("'%s': service not enabled.", service->name);
		errno = EACCES;
		return daemon_error(dir, "service not enabled");
	}

	if (!(path = path_ok(dir)))
		return daemon_error(dir, "no such repository");

	/*
	 * Security on the cheap.
	 *
	 * We want a readable HEAD, usable "objects" directory, and

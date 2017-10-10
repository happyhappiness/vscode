	const char *rla = getenv("GIT_REFLOG_ACTION");

	if (!rla)
		rla = "(reflog update)";
	if (snprintf(msg, sizeof(msg), "%s: %s", rla, action) >= sizeof(msg))
		warning("reflog message too long: %.*s...", 50, msg);
	return update_ref(msg, refname, sha1, oldval, 0,
			  UPDATE_REFS_QUIET_ON_ERR);
}

static int update_local_ref(const char *name,
			    const char *new_head,
			    const char *note,
			    int verbose, int force)

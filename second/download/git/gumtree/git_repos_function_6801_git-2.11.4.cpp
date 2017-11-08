static int update_ref_env(const char *action,
		      const char *refname,
		      unsigned char *sha1,
		      unsigned char *oldval)
{
	char msg[1024];
	const char *rla = getenv("GIT_REFLOG_ACTION");

	if (!rla)
		rla = "(reflog update)";
	if (snprintf(msg, sizeof(msg), "%s: %s", rla, action) >= sizeof(msg))
		warning("reflog message too long: %.*s...", 50, msg);
	return update_ref(msg, refname, sha1, oldval, 0,
			  UPDATE_REFS_QUIET_ON_ERR);
}
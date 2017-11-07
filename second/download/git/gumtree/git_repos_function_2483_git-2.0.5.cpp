static int update_ref_write(const char *action, const char *refname,
			    const unsigned char *sha1, struct ref_lock *lock,
			    enum action_on_err onerr)
{
	if (write_ref_sha1(lock, sha1, action) < 0) {
		const char *str = "Cannot update the ref '%s'.";
		switch (onerr) {
		case MSG_ON_ERR: error(str, refname); break;
		case DIE_ON_ERR: die(str, refname); break;
		case QUIET_ON_ERR: break;
		}
		return 1;
	}
	return 0;
}
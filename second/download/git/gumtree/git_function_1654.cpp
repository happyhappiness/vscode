static int update_ref_write(const char *action, const char *refname,
			    const unsigned char *sha1, struct ref_lock *lock,
			    struct strbuf *err, enum action_on_err onerr)
{
	if (write_ref_sha1(lock, sha1, action) < 0) {
		const char *str = "Cannot update the ref '%s'.";
		if (err)
			strbuf_addf(err, str, refname);

		switch (onerr) {
		case UPDATE_REFS_MSG_ON_ERR: error(str, refname); break;
		case UPDATE_REFS_DIE_ON_ERR: die(str, refname); break;
		case UPDATE_REFS_QUIET_ON_ERR: break;
		}
		return 1;
	}
	return 0;
}
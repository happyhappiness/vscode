static struct ref_lock *update_ref_lock(const char *refname,
					const unsigned char *oldval,
					int flags, int *type_p,
					enum action_on_err onerr)
{
	struct ref_lock *lock;
	lock = lock_any_ref_for_update(refname, oldval, flags, type_p);
	if (!lock) {
		const char *str = "Cannot lock the ref '%s'.";
		switch (onerr) {
		case UPDATE_REFS_MSG_ON_ERR: error(str, refname); break;
		case UPDATE_REFS_DIE_ON_ERR: die(str, refname); break;
		case UPDATE_REFS_QUIET_ON_ERR: break;
		}
	}
	return lock;
}
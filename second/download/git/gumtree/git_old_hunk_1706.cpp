static int s_update_ref(const char *action,
			struct ref *ref,
			int check_old)
{
	char msg[1024];
	char *rla = getenv("GIT_REFLOG_ACTION");
	static struct ref_lock *lock;

	if (dry_run)
		return 0;
	if (!rla)
		rla = default_rla.buf;
	snprintf(msg, sizeof(msg), "%s: %s", rla, action);
	lock = lock_any_ref_for_update(ref->name,
				       check_old ? ref->old_sha1 : NULL,
				       0, NULL);
	if (!lock)
		return errno == ENOTDIR ? STORE_REF_ERROR_DF_CONFLICT :
					  STORE_REF_ERROR_OTHER;
	if (write_ref_sha1(lock, ref->new_sha1, msg) < 0)
		return errno == ENOTDIR ? STORE_REF_ERROR_DF_CONFLICT :
					  STORE_REF_ERROR_OTHER;
	return 0;
}

#define REFCOL_WIDTH  10

static int update_local_ref(struct ref *ref,
			    const char *remote,

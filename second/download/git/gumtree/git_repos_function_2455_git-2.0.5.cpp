static void prune_ref(struct ref_to_prune *r)
{
	struct ref_lock *lock = lock_ref_sha1(r->name + 5, r->sha1);

	if (lock) {
		unlink_or_warn(git_path("%s", r->name));
		unlock_ref(lock);
		try_remove_empty_parents(r->name);
	}
}
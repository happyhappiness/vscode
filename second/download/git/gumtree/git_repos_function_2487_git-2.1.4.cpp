static void prune_ref(struct ref_to_prune *r)
{
	struct ref_lock *lock = lock_any_ref_for_update(r->name, r->sha1,
							0, NULL);

	if (lock) {
		unlink_or_warn(git_path("%s", r->name));
		unlock_ref(lock);
		try_remove_empty_parents(r->name);
	}
}
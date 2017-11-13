static void update_store_old_sha1(struct ref_update *update,
				  const char *oldvalue)
{
	if (*oldvalue && get_sha1(oldvalue, update->old_sha1))
		die("invalid old value for ref %s: %s",
		    update->ref_name, oldvalue);

	/* We have an old value if non-empty, or if empty without -z */
	update->have_old = *oldvalue || line_termination;
}
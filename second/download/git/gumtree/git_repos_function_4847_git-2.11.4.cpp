static int post_checkout_hook(struct commit *old, struct commit *new,
			      int changed)
{
	return run_hook_le(NULL, "post-checkout",
			   sha1_to_hex(old ? old->object.oid.hash : null_sha1),
			   sha1_to_hex(new ? new->object.oid.hash : null_sha1),
			   changed ? "1" : "0", NULL);
	/* "new" can be NULL when checking out from the index before
	   a commit exists. */

}
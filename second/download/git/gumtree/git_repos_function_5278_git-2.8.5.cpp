static int iterate_ref_map(void *cb_data, unsigned char sha1[20])
{
	struct ref **rm = cb_data;
	struct ref *ref = *rm;

	/*
	 * Skip anything missing a peer_ref, which we are not
	 * actually going to write a ref for.
	 */
	while (ref && !ref->peer_ref)
		ref = ref->next;
	/* Returning -1 notes "end of list" to the caller. */
	if (!ref)
		return -1;

	hashcpy(sha1, ref->old_oid.hash);
	*rm = ref->next;
	return 0;
}
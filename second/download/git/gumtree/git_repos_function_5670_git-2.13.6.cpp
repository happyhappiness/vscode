static int iterate_ref_map(void *cb_data, unsigned char sha1[20])
{
	struct ref **rm = cb_data;
	struct ref *ref = *rm;

	while (ref && ref->status == REF_STATUS_REJECT_SHALLOW)
		ref = ref->next;
	if (!ref)
		return -1; /* end of the list */
	*rm = ref->next;
	hashcpy(sha1, ref->old_oid.hash);
	return 0;
}
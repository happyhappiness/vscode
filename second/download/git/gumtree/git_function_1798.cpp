static int atomic_push_failure(struct send_pack_args *args,
			       struct ref *remote_refs,
			       struct ref *failing_ref)
{
	struct ref *ref;
	/* Mark other refs as failed */
	for (ref = remote_refs; ref; ref = ref->next) {
		if (!ref->peer_ref && !args->send_mirror)
			continue;

		switch (ref->status) {
		case REF_STATUS_EXPECTING_REPORT:
			ref->status = REF_STATUS_ATOMIC_PUSH_FAILED;
			continue;
		default:
			break; /* do nothing */
		}
	}
	return error("atomic push failed for ref %s. status: %d\n",
		     failing_ref->name, failing_ref->status);
}
static int ref_update_to_be_sent(const struct ref *ref, const struct send_pack_args *args)
{
	if (!ref->peer_ref && !args->send_mirror)
		return 0;

	/* Check for statuses set by set_ref_status_for_push() */
	switch (ref->status) {
	case REF_STATUS_REJECT_NONFASTFORWARD:
	case REF_STATUS_REJECT_ALREADY_EXISTS:
	case REF_STATUS_REJECT_FETCH_FIRST:
	case REF_STATUS_REJECT_NEEDS_FORCE:
	case REF_STATUS_REJECT_STALE:
	case REF_STATUS_REJECT_NODELETE:
	case REF_STATUS_UPTODATE:
		return 0;
	default:
		return 1;
	}
}
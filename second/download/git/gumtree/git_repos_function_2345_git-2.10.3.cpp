static int check_to_send_update(const struct ref *ref, const struct send_pack_args *args)
{
	if (!ref->peer_ref && !args->send_mirror)
		return CHECK_REF_NO_PUSH;

	/* Check for statuses set by set_ref_status_for_push() */
	switch (ref->status) {
	case REF_STATUS_REJECT_NONFASTFORWARD:
	case REF_STATUS_REJECT_ALREADY_EXISTS:
	case REF_STATUS_REJECT_FETCH_FIRST:
	case REF_STATUS_REJECT_NEEDS_FORCE:
	case REF_STATUS_REJECT_STALE:
	case REF_STATUS_REJECT_NODELETE:
		return CHECK_REF_STATUS_REJECTED;
	case REF_STATUS_UPTODATE:
		return CHECK_REF_UPTODATE;
	default:
		return 0;
	}
}
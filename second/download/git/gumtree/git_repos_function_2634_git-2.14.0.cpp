void transport_update_tracking_ref(struct remote *remote, struct ref *ref, int verbose)
{
	struct refspec rs;

	if (ref->status != REF_STATUS_OK && ref->status != REF_STATUS_UPTODATE)
		return;

	rs.src = ref->name;
	rs.dst = NULL;

	if (!remote_find_tracking(remote, &rs)) {
		if (verbose)
			fprintf(stderr, "updating local tracking ref '%s'\n", rs.dst);
		if (ref->deletion) {
			delete_ref(NULL, rs.dst, NULL, 0);
		} else
			update_ref("update by push", rs.dst,
					ref->new_oid.hash, NULL, 0, 0);
		free(rs.dst);
	}
}
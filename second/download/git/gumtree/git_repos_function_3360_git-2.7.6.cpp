static int push_update_refs_status(struct helper_data *data,
				    struct ref *remote_refs,
				    int flags)
{
	struct strbuf buf = STRBUF_INIT;
	struct ref *ref = remote_refs;
	int ret = 0;

	for (;;) {
		char *private;

		if (recvline(data, &buf)) {
			ret = 1;
			break;
		}

		if (!buf.len)
			break;

		if (push_update_ref_status(&buf, &ref, remote_refs))
			continue;

		if (flags & TRANSPORT_PUSH_DRY_RUN || !data->refspecs || data->no_private_update)
			continue;

		/* propagate back the update to the remote namespace */
		private = apply_refspecs(data->refspecs, data->refspec_nr, ref->name);
		if (!private)
			continue;
		update_ref("update by helper", private, ref->new_oid.hash, NULL, 0, 0);
		free(private);
	}
	strbuf_release(&buf);
	return ret;
}
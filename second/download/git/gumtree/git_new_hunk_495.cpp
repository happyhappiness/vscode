				struct notes_merge_pair *p)
{
	mmbuffer_t result_buf;
	mmfile_t base, local, remote;
	int status;

	read_mmblob(&base, &p->base);
	read_mmblob(&local, &p->local);
	read_mmblob(&remote, &p->remote);

	status = ll_merge(&result_buf, oid_to_hex(&p->obj), &base, NULL,
			  &local, o->local_ref, &remote, o->remote_ref, NULL);

	free(base.ptr);
	free(local.ptr);
	free(remote.ptr);

	if ((status < 0) || !result_buf.ptr)
		die("Failed to execute internal merge");

	write_buf_to_worktree(p->obj.hash, result_buf.ptr, result_buf.size);
	free(result_buf.ptr);

	return status;
}

static int merge_one_change_manual(struct notes_merge_options *o,

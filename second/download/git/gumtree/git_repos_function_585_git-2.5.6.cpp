static void finish_bulk_checkin(struct bulk_checkin_state *state)
{
	struct object_id oid;
	struct strbuf packname = STRBUF_INIT;
	int i;

	if (!state->f)
		return;

	if (state->nr_written == 0) {
		close(state->f->fd);
		unlink(state->pack_tmp_name);
		goto clear_exit;
	} else if (state->nr_written == 1) {
		sha1close(state->f, oid.hash, CSUM_FSYNC);
	} else {
		int fd = sha1close(state->f, oid.hash, 0);
		fixup_pack_header_footer(fd, oid.hash, state->pack_tmp_name,
					 state->nr_written, oid.hash,
					 state->offset);
		close(fd);
	}

	strbuf_addf(&packname, "%s/pack/pack-", get_object_directory());
	finish_tmp_packfile(&packname, state->pack_tmp_name,
			    state->written, state->nr_written,
			    &state->pack_idx_opts, oid.hash);
	for (i = 0; i < state->nr_written; i++)
		free(state->written[i]);

clear_exit:
	free(state->written);
	memset(state, 0, sizeof(*state));

	strbuf_release(&packname);
	/* Make objects we just wrote available to ourselves */
	reprepare_packed_git();
}
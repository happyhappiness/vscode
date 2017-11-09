static int deflate_to_pack(struct bulk_checkin_state *state,
			   unsigned char result_sha1[],
			   int fd, size_t size,
			   enum object_type type, const char *path,
			   unsigned flags)
{
	off_t seekback, already_hashed_to;
	git_SHA_CTX ctx;
	unsigned char obuf[16384];
	unsigned header_len;
	struct sha1file_checkpoint checkpoint;
	struct pack_idx_entry *idx = NULL;

	seekback = lseek(fd, 0, SEEK_CUR);
	if (seekback == (off_t) -1)
		return error("cannot find the current offset");

	header_len = xsnprintf((char *)obuf, sizeof(obuf), "%s %" PRIuMAX,
			       typename(type), (uintmax_t)size) + 1;
	git_SHA1_Init(&ctx);
	git_SHA1_Update(&ctx, obuf, header_len);

	/* Note: idx is non-NULL when we are writing */
	if ((flags & HASH_WRITE_OBJECT) != 0)
		idx = xcalloc(1, sizeof(*idx));

	already_hashed_to = 0;

	while (1) {
		prepare_to_stream(state, flags);
		if (idx) {
			sha1file_checkpoint(state->f, &checkpoint);
			idx->offset = state->offset;
			crc32_begin(state->f);
		}
		if (!stream_to_pack(state, &ctx, &already_hashed_to,
				    fd, size, type, path, flags))
			break;
		/*
		 * Writing this object to the current pack will make
		 * it too big; we need to truncate it, start a new
		 * pack, and write into it.
		 */
		if (!idx)
			die("BUG: should not happen");
		sha1file_truncate(state->f, &checkpoint);
		state->offset = checkpoint.offset;
		finish_bulk_checkin(state);
		if (lseek(fd, seekback, SEEK_SET) == (off_t) -1)
			return error("cannot seek back");
	}
	git_SHA1_Final(result_sha1, &ctx);
	if (!idx)
		return 0;

	idx->crc32 = crc32_end(state->f);
	if (already_written(state, result_sha1)) {
		sha1file_truncate(state->f, &checkpoint);
		state->offset = checkpoint.offset;
		free(idx);
	} else {
		hashcpy(idx->oid.hash, result_sha1);
		ALLOC_GROW(state->written,
			   state->nr_written + 1,
			   state->alloc_written);
		state->written[state->nr_written++] = idx;
	}
	return 0;
}
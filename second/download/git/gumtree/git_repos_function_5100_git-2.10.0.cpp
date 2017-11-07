static void parse_pack_objects(unsigned char *sha1)
{
	int i, nr_delays = 0;
	struct ofs_delta_entry *ofs_delta = ofs_deltas;
	unsigned char ref_delta_sha1[20];
	struct stat st;

	if (verbose)
		progress = start_progress(
				from_stdin ? _("Receiving objects") : _("Indexing objects"),
				nr_objects);
	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];
		void *data = unpack_raw_entry(obj, &ofs_delta->offset,
					      ref_delta_sha1, obj->idx.sha1);
		obj->real_type = obj->type;
		if (obj->type == OBJ_OFS_DELTA) {
			nr_ofs_deltas++;
			ofs_delta->obj_no = i;
			ofs_delta++;
		} else if (obj->type == OBJ_REF_DELTA) {
			ALLOC_GROW(ref_deltas, nr_ref_deltas + 1, ref_deltas_alloc);
			hashcpy(ref_deltas[nr_ref_deltas].sha1, ref_delta_sha1);
			ref_deltas[nr_ref_deltas].obj_no = i;
			nr_ref_deltas++;
		} else if (!data) {
			/* large blobs, check later */
			obj->real_type = OBJ_BAD;
			nr_delays++;
		} else
			sha1_object(data, NULL, obj->size, obj->type, obj->idx.sha1);
		free(data);
		display_progress(progress, i+1);
	}
	objects[i].idx.offset = consumed_bytes;
	stop_progress(&progress);

	/* Check pack integrity */
	flush();
	git_SHA1_Final(sha1, &input_ctx);
	if (hashcmp(fill(20), sha1))
		die(_("pack is corrupted (SHA1 mismatch)"));
	use(20);

	/* If input_fd is a file, we should have reached its end now. */
	if (fstat(input_fd, &st))
		die_errno(_("cannot fstat packfile"));
	if (S_ISREG(st.st_mode) &&
			lseek(input_fd, 0, SEEK_CUR) - input_len != st.st_size)
		die(_("pack has junk at the end"));

	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];
		if (obj->real_type != OBJ_BAD)
			continue;
		obj->real_type = obj->type;
		sha1_object(NULL, obj, obj->size, obj->type, obj->idx.sha1);
		nr_delays--;
	}
	if (nr_delays)
		die(_("confusion beyond insanity in parse_pack_objects()"));
}
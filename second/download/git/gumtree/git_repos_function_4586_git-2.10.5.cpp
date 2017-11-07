static void unpack_delta_entry(enum object_type type, unsigned long delta_size,
			       unsigned nr)
{
	void *delta_data, *base;
	unsigned long base_size;
	unsigned char base_sha1[20];

	if (type == OBJ_REF_DELTA) {
		hashcpy(base_sha1, fill(20));
		use(20);
		delta_data = get_data(delta_size);
		if (dry_run || !delta_data) {
			free(delta_data);
			return;
		}
		if (has_sha1_file(base_sha1))
			; /* Ok we have this one */
		else if (resolve_against_held(nr, base_sha1,
					      delta_data, delta_size))
			return; /* we are done */
		else {
			/* cannot resolve yet --- queue it */
			hashclr(obj_list[nr].sha1);
			add_delta_to_list(nr, base_sha1, 0, delta_data, delta_size);
			return;
		}
	} else {
		unsigned base_found = 0;
		unsigned char *pack, c;
		off_t base_offset;
		unsigned lo, mid, hi;

		pack = fill(1);
		c = *pack;
		use(1);
		base_offset = c & 127;
		while (c & 128) {
			base_offset += 1;
			if (!base_offset || MSB(base_offset, 7))
				die("offset value overflow for delta base object");
			pack = fill(1);
			c = *pack;
			use(1);
			base_offset = (base_offset << 7) + (c & 127);
		}
		base_offset = obj_list[nr].offset - base_offset;
		if (base_offset <= 0 || base_offset >= obj_list[nr].offset)
			die("offset value out of bound for delta base object");

		delta_data = get_data(delta_size);
		if (dry_run || !delta_data) {
			free(delta_data);
			return;
		}
		lo = 0;
		hi = nr;
		while (lo < hi) {
			mid = (lo + hi)/2;
			if (base_offset < obj_list[mid].offset) {
				hi = mid;
			} else if (base_offset > obj_list[mid].offset) {
				lo = mid + 1;
			} else {
				hashcpy(base_sha1, obj_list[mid].sha1);
				base_found = !is_null_sha1(base_sha1);
				break;
			}
		}
		if (!base_found) {
			/*
			 * The delta base object is itself a delta that
			 * has not been resolved yet.
			 */
			hashclr(obj_list[nr].sha1);
			add_delta_to_list(nr, null_sha1, base_offset, delta_data, delta_size);
			return;
		}
	}

	if (resolve_against_held(nr, base_sha1, delta_data, delta_size))
		return;

	base = read_sha1_file(base_sha1, &type, &base_size);
	if (!base) {
		error("failed to read delta-pack base object %s",
		      sha1_to_hex(base_sha1));
		if (!recover)
			exit(1);
		has_errors = 1;
		return;
	}
	resolve_delta(nr, type, base, base_size, delta_data, delta_size);
	free(base);
}
		die_errno("Unable to open marks file %s for writing.", file);

	for (i = 0; i < idnums.size; i++) {
		if (deco->base && deco->base->type == 1) {
			mark = ptr_to_mark(deco->decoration);
			if (fprintf(f, ":%"PRIu32" %s\n", mark,
				sha1_to_hex(deco->base->sha1)) < 0) {
			    e = 1;
			    break;
			}
		}
		deco++;
	}

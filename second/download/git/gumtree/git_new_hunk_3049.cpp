	unsigned int i;
	uint32_t mark;
	struct object_decoration *deco = idnums.hash;
	FILE *f;
	int e = 0;

	f = fopen_for_writing(file);
	if (!f)
		die_errno("Unable to open marks file %s for writing.", file);

	for (i = 0; i < idnums.size; i++) {
		if (deco->base && deco->base->type == 1) {
			mark = ptr_to_mark(deco->decoration);

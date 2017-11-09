static int xdl_recs_copy_0(int use_orig, xdfenv_t *xe, int i, int count, int needs_cr, int add_nl, char *dest)
{
	xrecord_t **recs;
	int size = 0;

	recs = (use_orig ? xe->xdf1.recs : xe->xdf2.recs) + i;

	if (count < 1)
		return 0;

	for (i = 0; i < count; size += recs[i++]->size)
		if (dest)
			memcpy(dest + size, recs[i]->ptr, recs[i]->size);
	if (add_nl) {
		i = recs[count - 1]->size;
		if (i == 0 || recs[count - 1]->ptr[i - 1] != '\n') {
			if (needs_cr) {
				if (dest)
					dest[size] = '\r';
				size++;
			}

			if (dest)
				dest[size] = '\n';
			size++;
		}
	}
	return size;
}
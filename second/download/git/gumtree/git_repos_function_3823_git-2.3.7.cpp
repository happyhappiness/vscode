static int fill_conflict_hunk(xdfenv_t *xe1, const char *name1,
			      xdfenv_t *xe2, const char *name2,
			      const char *name3,
			      int size, int i, int style,
			      xdmerge_t *m, char *dest, int marker_size)
{
	int marker1_size = (name1 ? strlen(name1) + 1 : 0);
	int marker2_size = (name2 ? strlen(name2) + 1 : 0);
	int marker3_size = (name3 ? strlen(name3) + 1 : 0);

	if (marker_size <= 0)
		marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	/* Before conflicting part */
	size += xdl_recs_copy(xe1, i, m->i1 - i, 0,
			      dest ? dest + size : NULL);

	if (!dest) {
		size += marker_size + 1 + marker1_size;
	} else {
		memset(dest + size, '<', marker_size);
		size += marker_size;
		if (marker1_size) {
			dest[size] = ' ';
			memcpy(dest + size + 1, name1, marker1_size - 1);
			size += marker1_size;
		}
		dest[size++] = '\n';
	}

	/* Postimage from side #1 */
	size += xdl_recs_copy(xe1, m->i1, m->chg1, 1,
			      dest ? dest + size : NULL);

	if (style == XDL_MERGE_DIFF3) {
		/* Shared preimage */
		if (!dest) {
			size += marker_size + 1 + marker3_size;
		} else {
			memset(dest + size, '|', marker_size);
			size += marker_size;
			if (marker3_size) {
				dest[size] = ' ';
				memcpy(dest + size + 1, name3, marker3_size - 1);
				size += marker3_size;
			}
			dest[size++] = '\n';
		}
		size += xdl_orig_copy(xe1, m->i0, m->chg0, 1,
				      dest ? dest + size : NULL);
	}

	if (!dest) {
		size += marker_size + 1;
	} else {
		memset(dest + size, '=', marker_size);
		size += marker_size;
		dest[size++] = '\n';
	}

	/* Postimage from side #2 */
	size += xdl_recs_copy(xe2, m->i2, m->chg2, 1,
			      dest ? dest + size : NULL);
	if (!dest) {
		size += marker_size + 1 + marker2_size;
	} else {
		memset(dest + size, '>', marker_size);
		size += marker_size;
		if (marker2_size) {
			dest[size] = ' ';
			memcpy(dest + size + 1, name2, marker2_size - 1);
			size += marker2_size;
		}
		dest[size++] = '\n';
	}
	return size;
}
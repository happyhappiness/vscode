static enum write_one_status write_one(struct sha1file *f,
				       struct object_entry *e,
				       off_t *offset)
{
	off_t size;
	int recursing;

	/*
	 * we set offset to 1 (which is an impossible value) to mark
	 * the fact that this object is involved in "write its base
	 * first before writing a deltified object" recursion.
	 */
	recursing = (e->idx.offset == 1);
	if (recursing) {
		warning("recursive delta detected for object %s",
			oid_to_hex(&e->idx.oid));
		return WRITE_ONE_RECURSIVE;
	} else if (e->idx.offset || e->preferred_base) {
		/* offset is non zero if object is written already. */
		return WRITE_ONE_SKIP;
	}

	/* if we are deltified, write out base object first. */
	if (e->delta) {
		e->idx.offset = 1; /* now recurse */
		switch (write_one(f, e->delta, offset)) {
		case WRITE_ONE_RECURSIVE:
			/* we cannot depend on this one */
			e->delta = NULL;
			break;
		default:
			break;
		case WRITE_ONE_BREAK:
			e->idx.offset = recursing;
			return WRITE_ONE_BREAK;
		}
	}

	e->idx.offset = *offset;
	size = write_object(f, e, *offset);
	if (!size) {
		e->idx.offset = recursing;
		return WRITE_ONE_BREAK;
	}
	written_list[nr_written++] = &e->idx;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(*offset, size))
		die("pack too large for current definition of off_t");
	*offset += size;
	return WRITE_ONE_WRITTEN;
}
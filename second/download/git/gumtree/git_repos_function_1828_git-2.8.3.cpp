int unpack_object_header(struct packed_git *p,
			 struct pack_window **w_curs,
			 off_t *curpos,
			 unsigned long *sizep)
{
	unsigned char *base;
	unsigned long left;
	unsigned long used;
	enum object_type type;

	/* use_pack() assures us we have [base, base + 20) available
	 * as a range that we can look at.  (Its actually the hash
	 * size that is assured.)  With our object header encoding
	 * the maximum deflated object size is 2^137, which is just
	 * insane, so we know won't exceed what we have been given.
	 */
	base = use_pack(p, w_curs, *curpos, &left);
	used = unpack_object_header_buffer(base, left, &type, sizep);
	if (!used) {
		type = OBJ_BAD;
	} else
		*curpos += used;

	return type;
}
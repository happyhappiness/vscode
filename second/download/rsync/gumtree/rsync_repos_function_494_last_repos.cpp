static void send_ida_entries(int f, const ida_entries *idal)
{
	id_access *ida;
	size_t count = idal->count;

	write_varint(f, idal->count);

	for (ida = idal->idas; count--; ida++) {
		uint32 xbits = ida->access << 2;
		const char *name;
		if (ida->access & NAME_IS_USER) {
			xbits |= XFLAG_NAME_IS_USER;
			name = numeric_ids ? NULL : add_uid(ida->id);
		} else
			name = numeric_ids ? NULL : add_gid(ida->id);
		write_varint(f, ida->id);
		if (inc_recurse && name) {
			int len = strlen(name);
			write_varint(f, xbits | XFLAG_NAME_FOLLOWS);
			write_byte(f, len);
			write_buf(f, name, len);
		} else
			write_varint(f, xbits);
	}
}
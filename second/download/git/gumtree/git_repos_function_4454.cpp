static void unpack_non_delta_entry(enum object_type type, unsigned long size,
				   unsigned nr)
{
	void *buf = get_data(size);

	if (!dry_run && buf)
		write_object(nr, type, buf, size);
	else
		free(buf);
}
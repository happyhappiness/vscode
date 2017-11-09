void write_del_stats(int f)
{
	if (read_batch)
		write_int(f, NDX_DEL_STATS);
	else
		write_ndx(f, NDX_DEL_STATS);
	write_varint(f, stats.deleted_files - stats.deleted_dirs
		      - stats.deleted_symlinks - stats.deleted_devices
		      - stats.deleted_specials);
	write_varint(f, stats.deleted_dirs);
	write_varint(f, stats.deleted_symlinks);
	write_varint(f, stats.deleted_devices);
	write_varint(f, stats.deleted_specials);
}
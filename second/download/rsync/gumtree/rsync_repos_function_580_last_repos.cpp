void read_del_stats(int f)
{
	stats.deleted_files = read_varint(f);
	stats.deleted_files += stats.deleted_dirs = read_varint(f);
	stats.deleted_files += stats.deleted_symlinks = read_varint(f);
	stats.deleted_files += stats.deleted_devices = read_varint(f);
	stats.deleted_files += stats.deleted_specials = read_varint(f);
}
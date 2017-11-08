int make_backup(const char *fname)
{
	if (backup_dir)
		return keep_backup(fname);
	return make_simple_backup(fname);
}
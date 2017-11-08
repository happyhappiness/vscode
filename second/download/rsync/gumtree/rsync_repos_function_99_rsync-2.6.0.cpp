int make_backup(char *fname)
{
	if (backup_dir)
		return (keep_backup(fname));
	else
		return (make_simple_backup(fname));
}
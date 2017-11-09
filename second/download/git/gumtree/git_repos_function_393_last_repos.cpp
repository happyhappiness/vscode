static int should_delete_shared_index(const char *shared_index_path)
{
	struct stat st;
	unsigned long expiration;

	/* Check timestamp */
	expiration = get_shared_index_expire_date();
	if (!expiration)
		return 0;
	if (stat(shared_index_path, &st))
		return error_errno(_("could not stat '%s'"), shared_index_path);
	if (st.st_mtime > expiration)
		return 0;

	return 1;
}
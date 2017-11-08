static int ensure_leading_directories(char *path)
{
	switch (safe_create_leading_directories(path)) {
		case SCLD_OK:
		case SCLD_EXISTS:
			return 0;
		default:
			return error(_("could not create leading directories "
				       "of '%s'"), path);
	}
}
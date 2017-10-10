{
	return S_ISGITLINK(mode) ? rmdir_or_warn(file) : unlink_or_warn(file);
}

void warn_on_inaccessible(const char *path)
{
	warning(_("unable to access '%s': %s"), path, strerror(errno));
}

static int access_error_is_ok(int err, unsigned flag)
{
	return err == ENOENT || err == ENOTDIR ||
		((flag & ACCESS_EACCES_OK) && err == EACCES);

void warn_on_inaccessible(const char *path)
{
	warning(_("unable to access '%s': %s"), path, strerror(errno));
}
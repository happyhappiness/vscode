static void warn_on_inaccessible(const char *path)
{
	warning_errno(_("unable to access '%s'"), path);
}
int unlink_or_warn(const char *file)
{
	return warn_if_unremovable("unlink", file, unlink(file));
}
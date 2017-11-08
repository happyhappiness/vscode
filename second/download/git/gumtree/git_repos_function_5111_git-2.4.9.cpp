static int resolve_undo_clear_callback(const struct option *opt,
				const char *arg, int unset)
{
	resolve_undo_clear();
	return 0;
}
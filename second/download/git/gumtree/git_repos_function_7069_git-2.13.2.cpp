static void remove_keep(void)
{
	if (keep && *keep)
		unlink(keep);
}
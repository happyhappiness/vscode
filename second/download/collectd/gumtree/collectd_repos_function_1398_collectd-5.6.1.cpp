static void printerr (void)
{
	int ecode = tcrdbecode(rdb);
	ERROR ("tokyotyrant plugin: error: %d, %s",
			ecode, tcrdberrmsg(ecode));
}
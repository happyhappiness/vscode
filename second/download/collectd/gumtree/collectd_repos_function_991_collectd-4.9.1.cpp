static void printerr()
{
	int ecode = tcrdbecode(rdb);
	ERROR ("tokyotyrant plugin: error: %d, %s",
			ecode, tcrdberrmsg(ecode));
}
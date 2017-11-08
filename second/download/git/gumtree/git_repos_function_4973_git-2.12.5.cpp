static int collect_one_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
				  const char *ident, unsigned long timestamp,
				  int tz, const char *message, void *cbdata)
{
	struct rev_collect *revs = cbdata;

	if (revs->initial) {
		revs->initial = 0;
		add_one_commit(osha1, revs);
	}
	add_one_commit(nsha1, revs);
	return 0;
}
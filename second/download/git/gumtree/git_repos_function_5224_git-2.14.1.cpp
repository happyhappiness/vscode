static int collect_one_reflog_ent(struct object_id *ooid, struct object_id *noid,
				  const char *ident, timestamp_t timestamp,
				  int tz, const char *message, void *cbdata)
{
	struct rev_collect *revs = cbdata;

	if (revs->initial) {
		revs->initial = 0;
		add_one_commit(ooid, revs);
	}
	add_one_commit(noid, revs);
	return 0;
}
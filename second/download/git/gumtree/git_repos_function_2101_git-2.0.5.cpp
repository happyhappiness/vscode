static int add_one_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	struct object *object;
	struct rev_info *revs = (struct rev_info *)cb_data;

	object = parse_object(osha1);
	if (object)
		add_pending_object(revs, object, "");
	object = parse_object(nsha1);
	if (object)
		add_pending_object(revs, object, "");
	return 0;
}
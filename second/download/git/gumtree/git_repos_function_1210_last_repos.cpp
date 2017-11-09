void add_head_to_pending(struct rev_info *revs)
{
	struct object_id oid;
	struct object *obj;
	if (get_oid("HEAD", &oid))
		return;
	obj = parse_object(&oid);
	if (!obj)
		return;
	add_pending_object(revs, obj, "HEAD");
}
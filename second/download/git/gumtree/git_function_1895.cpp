static void check_object(struct object *obj)
{
	if (verbose)
		fprintf(stderr, "Checking %s\n", sha1_to_hex(obj->sha1));

	if (obj->flags & REACHABLE)
		check_reachable_object(obj);
	else
		check_unreachable_object(obj);
}
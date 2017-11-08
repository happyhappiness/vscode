static int replace_object(const char *object_ref, const char *replace_ref, int force)
{
	struct object_id object, repl;

	if (get_oid(object_ref, &object))
		die("Failed to resolve '%s' as a valid ref.", object_ref);
	if (get_oid(replace_ref, &repl))
		die("Failed to resolve '%s' as a valid ref.", replace_ref);

	return replace_object_oid(object_ref, &object, replace_ref, &repl, force);
}
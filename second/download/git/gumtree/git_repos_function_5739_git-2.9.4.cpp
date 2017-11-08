static int replace_object(const char *object_ref, const char *replace_ref, int force)
{
	unsigned char object[20], repl[20];

	if (get_sha1(object_ref, object))
		die("Failed to resolve '%s' as a valid ref.", object_ref);
	if (get_sha1(replace_ref, repl))
		die("Failed to resolve '%s' as a valid ref.", replace_ref);

	return replace_object_sha1(object_ref, object, replace_ref, repl, force);
}
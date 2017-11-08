struct commit *lookup_commit_or_die(const struct object_id *oid, const char *ref_name)
{
	struct commit *c = lookup_commit_reference(oid);
	if (!c)
		die(_("could not parse %s"), ref_name);
	if (oidcmp(oid, &c->object.oid)) {
		warning(_("%s %s is not a commit!"),
			ref_name, oid_to_hex(oid));
	}
	return c;
}
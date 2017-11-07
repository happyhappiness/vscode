static const unsigned char *match_points_at(struct sha1_array *points_at,
					    const unsigned char *sha1,
					    const char *refname)
{
	const unsigned char *tagged_sha1 = NULL;
	struct object *obj;

	if (sha1_array_lookup(points_at, sha1) >= 0)
		return sha1;
	obj = parse_object(sha1);
	if (!obj)
		die(_("malformed object at '%s'"), refname);
	if (obj->type == OBJ_TAG)
		tagged_sha1 = ((struct tag *)obj)->tagged->oid.hash;
	if (tagged_sha1 && sha1_array_lookup(points_at, tagged_sha1) >= 0)
		return tagged_sha1;
	return NULL;
}
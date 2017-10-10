		if (!wildmatch(p, refname, WM_PATHNAME, NULL))
			return 1;
	}
	return 0;
}

/* Return 1 if the refname matches one of the patterns, otherwise 0. */
static int filter_pattern_match(struct ref_filter *filter, const char *refname)
{
	if (!*filter->name_patterns)
		return 1; /* No pattern always matches */
	if (filter->match_as_path)
		return match_name_as_path(filter->name_patterns, refname);
	return match_pattern(filter->name_patterns, refname);
}

/*
 * Given a ref (sha1, refname), check if the ref belongs to the array
 * of sha1s. If the given ref is a tag, check if the given tag points
 * at one of the sha1s in the given sha1 array.
 * the given sha1_array.
 * NEEDSWORK:
 * 1. Only a single level of inderection is obtained, we might want to
 * change this to account for multiple levels (e.g. annotated tags
 * pointing to annotated tags pointing to a commit.)
 * 2. As the refs are cached we might know what refname peels to without
 * the need to parse the object via parse_object(). peel_ref() might be a
 * more efficient alternative to obtain the pointee.
 */
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

/* Allocate space for a new ref_array_item and copy the objectname and flag to it */
static struct ref_array_item *new_ref_array_item(const char *refname,
						 const unsigned char *objectname,
						 int flag)
{
	size_t len = strlen(refname);

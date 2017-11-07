static int check_ref(const char *name, int len, unsigned int flags)
{
	if (!flags)
		return 1;

	if (len < 5 || memcmp(name, "refs/", 5))
		return 0;

	/* Skip the "refs/" part */
	name += 5;
	len -= 5;

	/* REF_NORMAL means that we don't want the magic fake tag refs */
	if ((flags & REF_NORMAL) && check_refname_format(name, 0))
		return 0;

	/* REF_HEADS means that we want regular branch heads */
	if ((flags & REF_HEADS) && !memcmp(name, "heads/", 6))
		return 1;

	/* REF_TAGS means that we want tags */
	if ((flags & REF_TAGS) && !memcmp(name, "tags/", 5))
		return 1;

	/* All type bits clear means that we are ok with anything */
	return !(flags & ~REF_NORMAL);
}
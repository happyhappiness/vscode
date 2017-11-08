static const char *name_ref_abbrev(const char *refname, int shorten_unambiguous)
{
	if (shorten_unambiguous)
		refname = shorten_unambiguous_ref(refname, 0);
	else if (starts_with(refname, "refs/heads/"))
		refname = refname + 11;
	else if (starts_with(refname, "refs/"))
		refname = refname + 5;
	return refname;
}
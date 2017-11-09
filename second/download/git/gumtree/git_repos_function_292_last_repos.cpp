static combine_notes_fn parse_combine_notes_fn(const char *v)
{
	if (!strcasecmp(v, "overwrite"))
		return combine_notes_overwrite;
	else if (!strcasecmp(v, "ignore"))
		return combine_notes_ignore;
	else if (!strcasecmp(v, "concatenate"))
		return combine_notes_concatenate;
	else if (!strcasecmp(v, "cat_sort_uniq"))
		return combine_notes_cat_sort_uniq;
	else
		return NULL;
}
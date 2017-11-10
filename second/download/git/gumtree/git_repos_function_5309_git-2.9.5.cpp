static void add_people_info(struct strbuf *out,
			    struct string_list *authors,
			    struct string_list *committers)
{
	if (authors->nr)
		qsort(authors->items,
		      authors->nr, sizeof(authors->items[0]),
		      cmp_string_list_util_as_integral);
	if (committers->nr)
		qsort(committers->items,
		      committers->nr, sizeof(committers->items[0]),
		      cmp_string_list_util_as_integral);

	credit_people(out, authors, 'a');
	credit_people(out, committers, 'c');
}
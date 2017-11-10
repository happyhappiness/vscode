static void add_people_info(struct strbuf *out,
			    struct string_list *authors,
			    struct string_list *committers)
{
	QSORT(authors->items, authors->nr,
	      cmp_string_list_util_as_integral);
	QSORT(committers->items, committers->nr,
	      cmp_string_list_util_as_integral);

	credit_people(out, authors, 'a');
	credit_people(out, committers, 'c');
}
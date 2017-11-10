static void add_people_count(struct strbuf *out, struct string_list *people)
{
	if (people->nr == 1)
		strbuf_addstr(out, people->items[0].string);
	else if (people->nr == 2)
		strbuf_addf(out, "%s (%d) and %s (%d)",
			    people->items[0].string,
			    (int)util_as_integral(&people->items[0]),
			    people->items[1].string,
			    (int)util_as_integral(&people->items[1]));
	else if (people->nr)
		strbuf_addf(out, "%s (%d) and others",
			    people->items[0].string,
			    (int)util_as_integral(&people->items[0]));
}
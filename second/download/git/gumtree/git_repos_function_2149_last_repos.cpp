void print_string_list(const struct string_list *p, const char *text)
{
	int i;
	if ( text )
		printf("%s\n", text);
	for (i = 0; i < p->nr; i++)
		printf("%s:%p\n", p->items[i].string, p->items[i].util);
}
static struct string_list *get_parameters(void)
{
	if (!query_params) {
		const char *query = getenv("QUERY_STRING");

		query_params = xcalloc(1, sizeof(*query_params));
		while (query && *query) {
			char *name = url_decode_parameter_name(&query);
			char *value = url_decode_parameter_value(&query);
			struct string_list_item *i;

			i = string_list_lookup(query_params, name);
			if (!i)
				i = string_list_insert(query_params, name);
			else
				free(i->util);
			i->util = value;
		}
	}
	return query_params;
}
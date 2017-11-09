static void free_filters(filter_rule *ent)
{
	while (ent) {
		filter_rule *next = ent->next;
		free_filter(ent);
		ent = next;
	}
}
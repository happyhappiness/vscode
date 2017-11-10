static void cleanup(struct walker *walker)
{
	struct walker_data *data = walker->data;
	struct alt_base *alt, *alt_next;

	if (data) {
		alt = data->alt;
		while (alt) {
			alt_next = alt->next;

			free(alt->base);
			free(alt);

			alt = alt_next;
		}
		free(data);
		walker->data = NULL;
	}
}
static int fetch_ref(struct walker *walker, struct ref *ref)
{
	struct walker_data *data = walker->data;
	return http_fetch_ref(data->alt->base, ref);
}
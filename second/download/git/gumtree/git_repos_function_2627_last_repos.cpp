static int fetch(struct walker *walker, unsigned char *sha1)
{
	struct walker_data *data = walker->data;
	struct alt_base *altbase = data->alt;

	if (!fetch_object(walker, sha1))
		return 0;
	while (altbase) {
		if (!http_fetch_pack(walker, altbase, sha1))
			return 0;
		fetch_alternates(walker, data->alt->base);
		altbase = altbase->next;
	}
	return error("Unable to find %s under %s", sha1_to_hex(sha1),
		     data->alt->base);
}
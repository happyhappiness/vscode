static int fetch_indices(struct walker *walker, struct alt_base *repo)
{
	int ret;

	if (repo->got_indices)
		return 0;

	if (walker->get_verbosely)
		fprintf(stderr, "Getting pack list for %s\n", repo->base);

	switch (http_get_info_packs(repo->base, &repo->packs)) {
	case HTTP_OK:
	case HTTP_MISSING_TARGET:
		repo->got_indices = 1;
		ret = 0;
		break;
	default:
		repo->got_indices = 0;
		ret = -1;
	}

	return ret;
}
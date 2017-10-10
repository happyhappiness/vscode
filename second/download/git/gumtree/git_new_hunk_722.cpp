#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}

static int is_alternate_allowed(const char *url)
{
	const char *protocols[] = {
		"http", "https", "ftp", "ftps"
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(protocols); i++) {
		const char *end;
		if (skip_prefix(url, protocols[i], &end) &&
		    starts_with(end, "://"))
			break;
	}

	if (i >= ARRAY_SIZE(protocols)) {
		warning("ignoring alternate with unknown protocol: %s", url);
		return 0;
	}
	if (!is_transport_allowed(protocols[i], 0)) {
		warning("ignoring alternate with restricted protocol: %s", url);
		return 0;
	}

	return 1;
}

static void process_alternates_response(void *callback_data)
{
	struct alternates_request *alt_req =
		(struct alternates_request *)callback_data;
	struct walker *walker = alt_req->walker;
	struct walker_data *cdata = walker->data;

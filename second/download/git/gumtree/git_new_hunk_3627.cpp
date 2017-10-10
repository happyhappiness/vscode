	if (raw_url)
		url = transport_anonymize_url(raw_url);
	else
		url = xstrdup("foreign");

	rm = ref_map;
	if (check_connected(iterate_ref_map, &rm, NULL)) {
		rc = error(_("%s did not send all necessary objects\n"), url);
		goto abort;
	}

	prepare_format_display(ref_map);

	/*
	 * We do a pass for each fetch_head_status type in their enum order, so
	 * merged entries are written before not-for-merge. That lets readers
	 * use FETCH_HEAD as a refname to refer to the ref to be merged.
	 */
	for (want_status = FETCH_HEAD_MERGE;

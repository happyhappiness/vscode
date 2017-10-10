	}

	/* Send delete request */
	fprintf(stderr, "Removing remote branch '%s'\n", remote_ref->name);
	if (dry_run)
		return 0;
	url = xstrfmt("%s%s", repo->url, remote_ref->name);
	slot = get_active_slot();
	slot->results = &results;
	curl_setup_http_get(slot->curl, url, DAV_DELETE);
	if (start_active_slot(slot)) {
		run_active_slot(slot);
		free(url);

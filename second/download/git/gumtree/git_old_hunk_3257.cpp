			helper = xstrndup(url, p - url);
	}

	if (helper) {
		transport_helper_init(ret, helper);
	} else if (starts_with(url, "rsync:")) {
		transport_check_allowed("rsync");
		ret->get_refs_list = get_refs_via_rsync;
		ret->fetch = fetch_objs_via_rsync;
		ret->push = rsync_transport_push;
		ret->smart_options = NULL;
	} else if (url_is_local_not_ssh(url) && is_file(url) && is_bundle(url, 1)) {
		struct bundle_transport_data *data = xcalloc(1, sizeof(*data));
		transport_check_allowed("file");
		ret->data = data;
		ret->get_refs_list = get_refs_from_bundle;
		ret->fetch = fetch_refs_from_bundle;
		ret->disconnect = close_bundle;
		ret->smart_options = NULL;
	} else if (!is_url(url)
		|| starts_with(url, "file://")
		|| starts_with(url, "git://")
		|| starts_with(url, "ssh://")
		|| starts_with(url, "git+ssh://")
		|| starts_with(url, "ssh+git://")) {
		/*
		 * These are builtin smart transports; "allowed" transports
		 * will be checked individually in git_connect.
		 */
		struct git_transport_data *data = xcalloc(1, sizeof(*data));
		ret->data = data;

struct transport *transport_get(struct remote *remote, const char *url)
{
	const char *helper;
	struct transport *ret = xcalloc(1, sizeof(*ret));

	ret->progress = isatty(2);

	if (!remote)
		die("No remote provided to transport_get()");

	ret->got_remote_refs = 0;
	ret->remote = remote;
	helper = remote->foreign_vcs;

	if (!url && remote->url)
		url = remote->url[0];
	ret->url = url;

	/* maybe it is a foreign URL? */
	if (url) {
		const char *p = url;

		while (is_urlschemechar(p == url, *p))
			p++;
		if (starts_with(p, "::"))
			helper = xstrndup(url, p - url);
	}

	if (helper) {
		transport_helper_init(ret, helper);
	} else if (starts_with(url, "rsync:")) {
		ret->get_refs_list = get_refs_via_rsync;
		ret->fetch = fetch_objs_via_rsync;
		ret->push = rsync_transport_push;
		ret->smart_options = NULL;
	} else if (url_is_local_not_ssh(url) && is_file(url) && is_bundle(url, 1)) {
		struct bundle_transport_data *data = xcalloc(1, sizeof(*data));
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
		/* These are builtin smart transports. */
		struct git_transport_data *data = xcalloc(1, sizeof(*data));
		ret->data = data;
		ret->set_option = NULL;
		ret->get_refs_list = get_refs_via_connect;
		ret->fetch = fetch_refs_via_pack;
		ret->push_refs = git_transport_push;
		ret->connect = connect_git;
		ret->disconnect = disconnect_git;
		ret->smart_options = &(data->options);

		data->conn = NULL;
		data->got_remote_heads = 0;
	} else {
		/* Unknown protocol in URL. Pass to external handler. */
		int len = external_specification_len(url);
		char *handler = xmalloc(len + 1);
		handler[len] = 0;
		strncpy(handler, url, len);
		transport_helper_init(ret, handler);
	}

	if (ret->smart_options) {
		ret->smart_options->thin = 1;
		ret->smart_options->uploadpack = "git-upload-pack";
		if (remote->uploadpack)
			ret->smart_options->uploadpack = remote->uploadpack;
		ret->smart_options->receivepack = "git-receive-pack";
		if (remote->receivepack)
			ret->smart_options->receivepack = remote->receivepack;
	}

	return ret;
}
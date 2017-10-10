	refspec = parse_fetch_refspec(1, &fetch_pattern);

	strbuf_reset(&value);

	remote = remote_get(option_origin);
	transport = transport_get(remote, remote->url[0]);
	transport->cloning = 1;

	if (!transport->get_refs_list || (!is_local && !transport->fetch))
		die(_("Don't know how to clone %s"), transport->url);

	transport_set_option(transport, TRANS_OPT_KEEP, "yes");

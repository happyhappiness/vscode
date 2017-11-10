static int fetch_refs_via_pack(struct transport *transport,
			       int nr_heads, struct ref **to_fetch)
{
	struct git_transport_data *data = transport->data;
	struct ref *refs;
	char *dest = xstrdup(transport->url);
	struct fetch_pack_args args;
	struct ref *refs_tmp = NULL;

	memset(&args, 0, sizeof(args));
	args.uploadpack = data->options.uploadpack;
	args.keep_pack = data->options.keep;
	args.lock_pack = 1;
	args.use_thin_pack = data->options.thin;
	args.include_tag = data->options.followtags;
	args.verbose = (transport->verbose > 1);
	args.quiet = (transport->verbose < 0);
	args.no_progress = !transport->progress;
	args.depth = data->options.depth;
	args.check_self_contained_and_connected =
		data->options.check_self_contained_and_connected;
	args.cloning = transport->cloning;
	args.update_shallow = data->options.update_shallow;

	if (!data->got_remote_heads) {
		connect_setup(transport, 0, 0);
		get_remote_heads(data->fd[0], NULL, 0, &refs_tmp, 0,
				 NULL, &data->shallow);
		data->got_remote_heads = 1;
	}

	refs = fetch_pack(&args, data->fd, data->conn,
			  refs_tmp ? refs_tmp : transport->remote_refs,
			  dest, to_fetch, nr_heads, &data->shallow,
			  &transport->pack_lockfile);
	close(data->fd[0]);
	close(data->fd[1]);
	if (finish_connect(data->conn)) {
		free_refs(refs);
		refs = NULL;
	}
	data->conn = NULL;
	data->got_remote_heads = 0;
	data->options.self_contained_and_connected =
		args.self_contained_and_connected;

	free_refs(refs_tmp);
	free_refs(refs);
	free(dest);
	return (refs ? 0 : -1);
}
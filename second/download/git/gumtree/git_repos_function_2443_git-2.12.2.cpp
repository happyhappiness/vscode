static int git_transport_push(struct transport *transport, struct ref *remote_refs, int flags)
{
	struct git_transport_data *data = transport->data;
	struct send_pack_args args;
	int ret;

	if (!data->got_remote_heads) {
		struct ref *tmp_refs;
		connect_setup(transport, 1);

		get_remote_heads(data->fd[0], NULL, 0, &tmp_refs, REF_NORMAL,
				 NULL, &data->shallow);
		data->got_remote_heads = 1;
	}

	memset(&args, 0, sizeof(args));
	args.send_mirror = !!(flags & TRANSPORT_PUSH_MIRROR);
	args.force_update = !!(flags & TRANSPORT_PUSH_FORCE);
	args.use_thin_pack = data->options.thin;
	args.verbose = (transport->verbose > 0);
	args.quiet = (transport->verbose < 0);
	args.progress = transport->progress;
	args.dry_run = !!(flags & TRANSPORT_PUSH_DRY_RUN);
	args.porcelain = !!(flags & TRANSPORT_PUSH_PORCELAIN);
	args.atomic = !!(flags & TRANSPORT_PUSH_ATOMIC);
	args.push_options = transport->push_options;
	args.url = transport->url;

	if (flags & TRANSPORT_PUSH_CERT_ALWAYS)
		args.push_cert = SEND_PACK_PUSH_CERT_ALWAYS;
	else if (flags & TRANSPORT_PUSH_CERT_IF_ASKED)
		args.push_cert = SEND_PACK_PUSH_CERT_IF_ASKED;
	else
		args.push_cert = SEND_PACK_PUSH_CERT_NEVER;

	ret = send_pack(&args, data->fd, data->conn, remote_refs,
			&data->extra_have);

	close(data->fd[1]);
	close(data->fd[0]);
	ret |= finish_connect(data->conn);
	data->conn = NULL;
	data->got_remote_heads = 0;

	return ret;
}
static int fetch_with_fetch(struct transport *transport,
			    int nr_heads, struct ref **to_fetch)
{
	struct helper_data *data = transport->data;
	int i;
	struct strbuf buf = STRBUF_INIT;

	for (i = 0; i < nr_heads; i++) {
		const struct ref *posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;

		strbuf_addf(&buf, "fetch %s %s\n",
			    oid_to_hex(&posn->old_oid),
			    posn->symref ? posn->symref : posn->name);
	}

	strbuf_addch(&buf, '\n');
	sendline(data, &buf);

	while (1) {
		if (recvline(data, &buf))
			exit(128);

		if (starts_with(buf.buf, "lock ")) {
			const char *name = buf.buf + 5;
			if (transport->pack_lockfile)
				warning("%s also locked %s", data->name, name);
			else
				transport->pack_lockfile = xstrdup(name);
		}
		else if (data->check_connectivity &&
			 data->transport_options.check_self_contained_and_connected &&
			 !strcmp(buf.buf, "connectivity-ok"))
			data->transport_options.self_contained_and_connected = 1;
		else if (!buf.len)
			break;
		else
			warning("%s unexpectedly said: '%s'", data->name, buf.buf);
	}
	strbuf_release(&buf);
	return 0;
}
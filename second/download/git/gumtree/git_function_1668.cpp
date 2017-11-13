static int generate_push_cert(struct strbuf *req_buf,
			      const struct ref *remote_refs,
			      struct send_pack_args *args,
			      const char *cap_string,
			      const char *push_cert_nonce)
{
	const struct ref *ref;
	char *signing_key = xstrdup(get_signing_key());
	const char *cp, *np;
	struct strbuf cert = STRBUF_INIT;
	int update_seen = 0;

	strbuf_addf(&cert, "certificate version 0.1\n");
	strbuf_addf(&cert, "pusher %s ", signing_key);
	datestamp(&cert);
	strbuf_addch(&cert, '\n');
	if (args->url && *args->url) {
		char *anon_url = transport_anonymize_url(args->url);
		strbuf_addf(&cert, "pushee %s\n", anon_url);
		free(anon_url);
	}
	if (push_cert_nonce[0])
		strbuf_addf(&cert, "nonce %s\n", push_cert_nonce);
	strbuf_addstr(&cert, "\n");

	for (ref = remote_refs; ref; ref = ref->next) {
		if (!ref_update_to_be_sent(ref, args))
			continue;
		update_seen = 1;
		strbuf_addf(&cert, "%s %s %s\n",
			    sha1_to_hex(ref->old_sha1),
			    sha1_to_hex(ref->new_sha1),
			    ref->name);
	}
	if (!update_seen)
		goto free_return;

	if (sign_buffer(&cert, &cert, signing_key))
		die(_("failed to sign the push certificate"));

	packet_buf_write(req_buf, "push-cert%c%s", 0, cap_string);
	for (cp = cert.buf; cp < cert.buf + cert.len; cp = np) {
		np = next_line(cp, cert.buf + cert.len - cp);
		packet_buf_write(req_buf,
				 "%.*s", (int)(np - cp), cp);
	}
	packet_buf_write(req_buf, "push-cert-end\n");

free_return:
	free(signing_key);
	strbuf_release(&cert);
	return update_seen;
}
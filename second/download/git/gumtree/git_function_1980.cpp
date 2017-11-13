static int send_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	static const char *capabilities = "multi_ack thin-pack side-band"
		" side-band-64k ofs-delta shallow no-progress"
		" include-tag multi_ack_detailed";
	const char *refname_nons = strip_namespace(refname);
	unsigned char peeled[20];

	if (mark_our_ref(refname, sha1))
		return 0;

	if (capabilities) {
		struct strbuf symref_info = STRBUF_INIT;

		format_symref_info(&symref_info, cb_data);
		packet_write(1, "%s %s%c%s%s%s%s agent=%s\n",
			     sha1_to_hex(sha1), refname_nons,
			     0, capabilities,
			     allow_tip_sha1_in_want ? " allow-tip-sha1-in-want" : "",
			     stateless_rpc ? " no-done" : "",
			     symref_info.buf,
			     git_user_agent_sanitized());
		strbuf_release(&symref_info);
	} else {
		packet_write(1, "%s %s\n", sha1_to_hex(sha1), refname_nons);
	}
	capabilities = NULL;
	if (!peel_ref(refname, peeled))
		packet_write(1, "%s %s^{}\n", sha1_to_hex(peeled), refname_nons);
	return 0;
}
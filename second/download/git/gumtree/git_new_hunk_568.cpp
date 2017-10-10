}

static int send_ref(const char *refname, const struct object_id *oid,
		    int flag, void *cb_data)
{
	static const char *capabilities = "multi_ack thin-pack side-band"
		" side-band-64k ofs-delta shallow deepen-since deepen-not"
		" deepen-relative no-progress include-tag multi_ack_detailed";
	const char *refname_nons = strip_namespace(refname);
	struct object_id peeled;

	if (mark_our_ref(refname_nons, refname, oid))
		return 0;

	if (capabilities) {
		struct strbuf symref_info = STRBUF_INIT;

		format_symref_info(&symref_info, cb_data);
		packet_write_fmt(1, "%s %s%c%s%s%s%s%s agent=%s\n",
			     oid_to_hex(oid), refname_nons,
			     0, capabilities,
			     (allow_unadvertised_object_request & ALLOW_TIP_SHA1) ?
				     " allow-tip-sha1-in-want" : "",
			     (allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1) ?
				     " allow-reachable-sha1-in-want" : "",
			     stateless_rpc ? " no-done" : "",
			     symref_info.buf,
			     git_user_agent_sanitized());
		strbuf_release(&symref_info);
	} else {
		packet_write_fmt(1, "%s %s\n", oid_to_hex(oid), refname_nons);
	}
	capabilities = NULL;
	if (!peel_ref(refname, peeled.hash))
		packet_write_fmt(1, "%s %s^{}\n", oid_to_hex(&peeled), refname_nons);
	return 0;
}

static int find_symref(const char *refname, const struct object_id *oid,
		       int flag, void *cb_data)
{

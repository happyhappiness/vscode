int write_shallow_commits(struct strbuf *out, int use_pack_protocol,
			  const struct oid_array *extra)
{
	return write_shallow_commits_1(out, use_pack_protocol, extra, 0);
}
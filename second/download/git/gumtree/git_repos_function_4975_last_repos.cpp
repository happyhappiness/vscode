static int build_tag_object(struct strbuf *buf, int sign, struct object_id *result)
{
	if (sign && do_sign(buf) < 0)
		return error(_("unable to sign the tag"));
	if (write_sha1_file(buf->buf, buf->len, tag_type, result->hash) < 0)
		return error(_("unable to write tag file"));
	return 0;
}
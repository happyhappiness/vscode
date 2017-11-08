void strbuf_add_unique_abbrev(struct strbuf *sb, const unsigned char *sha1,
			      int abbrev_len)
{
	int r;
	strbuf_grow(sb, GIT_SHA1_HEXSZ + 1);
	r = find_unique_abbrev_r(sb->buf + sb->len, sha1, abbrev_len);
	strbuf_setlen(sb, sb->len + r);
}
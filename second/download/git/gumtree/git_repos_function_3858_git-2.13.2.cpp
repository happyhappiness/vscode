static void fetch_symref(const char *path, char **symref, unsigned char *sha1)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	struct strbuf buffer = STRBUF_INIT;
	const char *name;

	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
		die("Couldn't get %s for remote symref\n%s", url,
		    curl_errorstr);
	free(url);

	free(*symref);
	*symref = NULL;
	hashclr(sha1);

	if (buffer.len == 0)
		return;

	/* Cut off trailing newline. */
	strbuf_rtrim(&buffer);

	/* If it's a symref, set the refname; otherwise try for a sha1 */
	if (skip_prefix(buffer.buf, "ref: ", &name)) {
		*symref = xmemdupz(name, buffer.len - (name - buffer.buf));
	} else {
		get_sha1_hex(buffer.buf, sha1);
	}

	strbuf_release(&buffer);
}
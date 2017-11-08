static void fetch_symref(const char *path, char **symref, struct object_id *oid)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	struct strbuf buffer = STRBUF_INIT;
	const char *name;

	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
		die("Couldn't get %s for remote symref\n%s", url,
		    curl_errorstr);
	free(url);

	FREE_AND_NULL(*symref);
	oidclr(oid);

	if (buffer.len == 0)
		return;

	/* Cut off trailing newline. */
	strbuf_rtrim(&buffer);

	/* If it's a symref, set the refname; otherwise try for a sha1 */
	if (skip_prefix(buffer.buf, "ref: ", &name)) {
		*symref = xmemdupz(name, buffer.len - (name - buffer.buf));
	} else {
		get_oid_hex(buffer.buf, oid);
	}

	strbuf_release(&buffer);
}
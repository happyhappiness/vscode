static void fetch_symref(const char *path, char **symref, unsigned char *sha1)
{
	char *url;
	struct strbuf buffer = STRBUF_INIT;

	url = xmalloc(strlen(repo->url) + strlen(path) + 1);
	sprintf(url, "%s%s", repo->url, path);

	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
		die("Couldn't get %s for remote symref\n%s", url,
		    curl_errorstr);
	free(url);

	free(*symref);
	*symref = NULL;
	hashclr(sha1);

	if (buffer.len == 0)
		return;

	/* If it's a symref, set the refname; otherwise try for a sha1 */
	if (starts_with((char *)buffer.buf, "ref: ")) {
		*symref = xmemdupz((char *)buffer.buf + 5, buffer.len - 6);
	} else {
		get_sha1_hex(buffer.buf, sha1);
	}

	strbuf_release(&buffer);
}
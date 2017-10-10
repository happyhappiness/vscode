	free(url);
	return ret;
}

static void fetch_symref(const char *path, char **symref, unsigned char *sha1)
{
	char *url = xstrfmt("%s%s", repo->url, path);
	struct strbuf buffer = STRBUF_INIT;
	const char *name;

	if (http_get_strbuf(url, &buffer, NULL) != HTTP_OK)
		die("Couldn't get %s for remote symref\n%s", url,
		    curl_errorstr);
	free(url);


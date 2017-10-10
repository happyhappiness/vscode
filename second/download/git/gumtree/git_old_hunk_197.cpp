	free(url);
	return ret;
}

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


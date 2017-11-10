static int get_one_entry(struct remote *remote, void *priv)
{
	struct string_list *list = priv;
	struct strbuf url_buf = STRBUF_INIT;
	const char **url;
	int i, url_nr;

	if (remote->url_nr > 0) {
		strbuf_addf(&url_buf, "%s (fetch)", remote->url[0]);
		string_list_append(list, remote->name)->util =
				strbuf_detach(&url_buf, NULL);
	} else
		string_list_append(list, remote->name)->util = NULL;
	if (remote->pushurl_nr) {
		url = remote->pushurl;
		url_nr = remote->pushurl_nr;
	} else {
		url = remote->url;
		url_nr = remote->url_nr;
	}
	for (i = 0; i < url_nr; i++)
	{
		strbuf_addf(&url_buf, "%s (push)", url[i]);
		string_list_append(list, remote->name)->util =
				strbuf_detach(&url_buf, NULL);
	}

	return 0;
}
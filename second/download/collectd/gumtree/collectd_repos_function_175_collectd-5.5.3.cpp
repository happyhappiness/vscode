static void apache_free (apache_t *st)
{
	if (st == NULL)
		return;

	sfree (st->name);
	sfree (st->host);
	sfree (st->url);
	sfree (st->user);
	sfree (st->pass);
	sfree (st->cacert);
	sfree (st->ssl_ciphers);
	sfree (st->server);
	sfree (st->apache_buffer);
	if (st->curl) {
		curl_easy_cleanup(st->curl);
		st->curl = NULL;
	}
	sfree (st);
}
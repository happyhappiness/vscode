static int http_get_file(const char *url, const char *filename,
			 struct http_get_options *options)
{
	int ret;
	struct strbuf tmpfile = STRBUF_INIT;
	FILE *result;

	strbuf_addf(&tmpfile, "%s.temp", filename);
	result = fopen(tmpfile.buf, "a");
	if (!result) {
		error("Unable to open local file %s", tmpfile.buf);
		ret = HTTP_ERROR;
		goto cleanup;
	}

	ret = http_request_reauth(url, result, HTTP_REQUEST_FILE, options);
	fclose(result);

	if (ret == HTTP_OK && finalize_object_file(tmpfile.buf, filename))
		ret = HTTP_ERROR;
cleanup:
	strbuf_release(&tmpfile);
	return ret;
}
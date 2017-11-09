static void check_content_type(struct strbuf *hdr, const char *accepted_type)
{
	const char *actual_type = getenv("CONTENT_TYPE");

	if (!actual_type)
		actual_type = "";

	if (strcmp(actual_type, accepted_type)) {
		http_status(hdr, 415, "Unsupported Media Type");
		hdr_nocache(hdr);
		end_headers(hdr);
		format_write(1,
			"Expected POST with Content-Type '%s',"
			" but received '%s' instead.\n",
			accepted_type, actual_type);
		exit(0);
	}
}
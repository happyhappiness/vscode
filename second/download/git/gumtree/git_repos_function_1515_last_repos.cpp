void abort_http_object_request(struct http_object_request *freq)
{
	unlink_or_warn(freq->tmpfile);

	release_http_object_request(freq);
}
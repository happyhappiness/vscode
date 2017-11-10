char *url_decode_parameter_name(const char **query)
{
	struct strbuf out = STRBUF_INIT;
	return url_decode_internal(query, -1, "&=", &out, 1);
}
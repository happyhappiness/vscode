static int curl_trace(CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
	const char *text;
	enum { NO_FILTER = 0, DO_FILTER = 1 };

	switch (type) {
	case CURLINFO_TEXT:
		trace_printf_key(&trace_curl, "== Info: %s", data);
	default:		/* we ignore unknown types by default */
		return 0;

	case CURLINFO_HEADER_OUT:
		text = "=> Send header";
		curl_dump_header(text, (unsigned char *)data, size, DO_FILTER);
		break;
	case CURLINFO_DATA_OUT:
		text = "=> Send data";
		curl_dump_data(text, (unsigned char *)data, size);
		break;
	case CURLINFO_SSL_DATA_OUT:
		text = "=> Send SSL data";
		curl_dump_data(text, (unsigned char *)data, size);
		break;
	case CURLINFO_HEADER_IN:
		text = "<= Recv header";
		curl_dump_header(text, (unsigned char *)data, size, NO_FILTER);
		break;
	case CURLINFO_DATA_IN:
		text = "<= Recv data";
		curl_dump_data(text, (unsigned char *)data, size);
		break;
	case CURLINFO_SSL_DATA_IN:
		text = "<= Recv SSL data";
		curl_dump_data(text, (unsigned char *)data, size);
		break;
	}
	return 0;
}
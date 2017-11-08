const char *get_convert_attr_ascii(const char *path)
{
	struct conv_attrs ca;

	convert_attrs(&ca, path);
	switch (ca.attr_action) {
	case CRLF_UNDEFINED:
		return "";
	case CRLF_BINARY:
		return "-text";
	case CRLF_TEXT:
		return "text";
	case CRLF_TEXT_INPUT:
		return "text eol=lf";
	case CRLF_TEXT_CRLF:
		return "text eol=crlf";
	case CRLF_AUTO:
		return "text=auto";
	case CRLF_AUTO_CRLF:
		return "text=auto eol=crlf";
	case CRLF_AUTO_INPUT:
		return "text=auto eol=lf";
	}
	return "";
}
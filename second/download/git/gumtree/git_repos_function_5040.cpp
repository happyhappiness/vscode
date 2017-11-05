static const char *parse_pack_header(struct pack_header *hdr)
{
	switch (read_pack_header(0, hdr)) {
	case PH_ERROR_EOF:
		return "eof before pack header was fully read";

	case PH_ERROR_PACK_SIGNATURE:
		return "protocol error (pack signature mismatch detected)";

	case PH_ERROR_PROTOCOL:
		return "protocol error (pack version unsupported)";

	default:
		return "unknown error in parse_pack_header";

	case 0:
		return NULL;
	}
}
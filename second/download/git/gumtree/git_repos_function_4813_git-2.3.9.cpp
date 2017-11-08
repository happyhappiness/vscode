static void decode_header(struct strbuf *it)
{
	if (decode_header_bq(it))
		return;
	/* otherwise "it" is a straight copy of the input.
	 * This can be binary guck but there is no charset specified.
	 */
	if (metainfo_charset)
		convert_to_utf8(it, "");
}
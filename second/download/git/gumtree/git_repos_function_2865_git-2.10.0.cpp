static void select_getanyfile(struct strbuf *hdr)
{
	if (!getanyfile)
		forbidden(hdr, "Unsupported service: getanyfile");
}
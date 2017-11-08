static void hdr_nocache(struct strbuf *hdr)
{
	hdr_str(hdr, "Expires", "Fri, 01 Jan 1980 00:00:00 GMT");
	hdr_str(hdr, "Pragma", "no-cache");
	hdr_str(hdr, "Cache-Control", "no-cache, max-age=0, must-revalidate");
}
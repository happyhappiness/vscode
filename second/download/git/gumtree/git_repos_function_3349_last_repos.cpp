static void hdr_cache_forever(struct strbuf *hdr)
{
	timestamp_t now = time(NULL);
	hdr_date(hdr, "Date", now);
	hdr_date(hdr, "Expires", now + 31536000);
	hdr_str(hdr, "Cache-Control", "public, max-age=31536000");
}
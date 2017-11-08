char *url_normalize(const char *url, struct url_info *out_info)
{
	return url_normalize_1(url, out_info, 0);
}
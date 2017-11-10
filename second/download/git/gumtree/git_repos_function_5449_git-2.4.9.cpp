int fast_export_ls_rev(uint32_t rev, const char *path,
				uint32_t *mode, struct strbuf *dataref)
{
	ls_from_rev(rev, path);
	return parse_ls_response(get_response_line(), mode, dataref);
}
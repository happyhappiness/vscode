int fast_export_ls(const char *path, uint32_t *mode, struct strbuf *dataref)
{
	ls_from_active_commit(path);
	return parse_ls_response(get_response_line(), mode, dataref);
}
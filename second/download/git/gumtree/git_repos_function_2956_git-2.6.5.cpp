void ws_check_emit(const char *line, int len, unsigned ws_rule,
		   FILE *stream, const char *set,
		   const char *reset, const char *ws)
{
	(void)ws_check_emit_1(line, len, ws_rule, stream, set, reset, ws);
}
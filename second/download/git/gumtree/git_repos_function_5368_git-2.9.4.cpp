static void print_path(const char *path)
{
	if (!anonymize)
		print_path_1(path);
	else {
		static struct hashmap paths;
		static struct strbuf anon = STRBUF_INIT;

		anonymize_path(&anon, path, &paths, anonymize_path_component);
		print_path_1(anon.buf);
		strbuf_reset(&anon);
	}
}
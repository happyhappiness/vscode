static void update_file(struct merge_options *o,
			int clean,
			const unsigned char *sha,
			unsigned mode,
			const char *path)
{
	update_file_flags(o, sha, mode, path, o->call_depth || clean, !o->call_depth);
}
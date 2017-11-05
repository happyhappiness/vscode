static void write_pack_access_log(struct packed_git *p, off_t obj_offset)
{
	static FILE *log_file;

	if (!log_pack_access)
		log_pack_access = getenv("GIT_TRACE_PACK_ACCESS");
	if (!log_pack_access)
		log_pack_access = no_log_pack_access;
	if (log_pack_access == no_log_pack_access)
		return;

	if (!log_file) {
		log_file = fopen(log_pack_access, "w");
		if (!log_file) {
			error("cannot open pack access log '%s' for writing: %s",
			      log_pack_access, strerror(errno));
			log_pack_access = no_log_pack_access;
			return;
		}
	}
	fprintf(log_file, "%s %"PRIuMAX"\n",
		p->pack_name, (uintmax_t)obj_offset);
	fflush(log_file);
}
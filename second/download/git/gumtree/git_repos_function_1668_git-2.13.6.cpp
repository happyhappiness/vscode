static void unkeep_all_packs(void)
{
	struct strbuf name = STRBUF_INIT;
	int k;

	for (k = 0; k < pack_id; k++) {
		struct packed_git *p = all_packs[k];
		odb_pack_name(&name, p->sha1, "keep");
		unlink_or_warn(name.buf);
	}
	strbuf_release(&name);
}
void write_untracked_extension(struct strbuf *out, struct untracked_cache *untracked)
{
	struct ondisk_untracked_cache *ouc;
	struct write_data wd;
	unsigned char varbuf[16];
	int varint_len;
	size_t len = strlen(untracked->exclude_per_dir);

	FLEX_ALLOC_MEM(ouc, exclude_per_dir, untracked->exclude_per_dir, len);
	stat_data_to_disk(&ouc->info_exclude_stat, &untracked->ss_info_exclude.stat);
	stat_data_to_disk(&ouc->excludes_file_stat, &untracked->ss_excludes_file.stat);
	hashcpy(ouc->info_exclude_sha1, untracked->ss_info_exclude.sha1);
	hashcpy(ouc->excludes_file_sha1, untracked->ss_excludes_file.sha1);
	ouc->dir_flags = htonl(untracked->dir_flags);

	varint_len = encode_varint(untracked->ident.len, varbuf);
	strbuf_add(out, varbuf, varint_len);
	strbuf_addbuf(out, &untracked->ident);

	strbuf_add(out, ouc, ouc_size(len));
	free(ouc);
	ouc = NULL;

	if (!untracked->root) {
		varint_len = encode_varint(0, varbuf);
		strbuf_add(out, varbuf, varint_len);
		return;
	}

	wd.index      = 0;
	wd.check_only = ewah_new();
	wd.valid      = ewah_new();
	wd.sha1_valid = ewah_new();
	strbuf_init(&wd.out, 1024);
	strbuf_init(&wd.sb_stat, 1024);
	strbuf_init(&wd.sb_sha1, 1024);
	write_one_dir(untracked->root, &wd);

	varint_len = encode_varint(wd.index, varbuf);
	strbuf_add(out, varbuf, varint_len);
	strbuf_addbuf(out, &wd.out);
	ewah_serialize_strbuf(wd.valid, out);
	ewah_serialize_strbuf(wd.check_only, out);
	ewah_serialize_strbuf(wd.sha1_valid, out);
	strbuf_addbuf(out, &wd.sb_stat);
	strbuf_addbuf(out, &wd.sb_sha1);
	strbuf_addch(out, '\0'); /* safe guard for string lists */

	ewah_free(wd.valid);
	ewah_free(wd.check_only);
	ewah_free(wd.sha1_valid);
	strbuf_release(&wd.out);
	strbuf_release(&wd.sb_stat);
	strbuf_release(&wd.sb_sha1);
}
static void get_info_packs(char *arg)
{
	size_t objdirlen = strlen(get_object_directory());
	struct strbuf buf = STRBUF_INIT;
	struct packed_git *p;
	size_t cnt = 0;

	select_getanyfile();
	prepare_packed_git();
	for (p = packed_git; p; p = p->next) {
		if (p->pack_local)
			cnt++;
	}

	strbuf_grow(&buf, cnt * 53 + 2);
	for (p = packed_git; p; p = p->next) {
		if (p->pack_local)
			strbuf_addf(&buf, "P %s\n", p->pack_name + objdirlen + 6);
	}
	strbuf_addch(&buf, '\n');

	hdr_nocache();
	send_strbuf("text/plain; charset=utf-8", &buf);
	strbuf_release(&buf);
}
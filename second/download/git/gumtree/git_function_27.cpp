static void emit_porcelain(struct scoreboard *sb, struct blame_entry *ent,
			   int opt)
{
	int repeat = opt & OUTPUT_LINE_PORCELAIN;
	int cnt;
	const char *cp;
	struct origin *suspect = ent->suspect;
	char hex[41];

	strcpy(hex, sha1_to_hex(suspect->commit->object.sha1));
	printf("%s%c%d %d %d\n",
	       hex,
	       ent->guilty ? ' ' : '*', /* purely for debugging */
	       ent->s_lno + 1,
	       ent->lno + 1,
	       ent->num_lines);
	emit_porcelain_details(suspect, repeat);

	cp = nth_line(sb, ent->lno);
	for (cnt = 0; cnt < ent->num_lines; cnt++) {
		char ch;
		if (cnt) {
			printf("%s %d %d\n", hex,
			       ent->s_lno + 1 + cnt,
			       ent->lno + 1 + cnt);
			if (repeat)
				emit_porcelain_details(suspect, 1);
		}
		putchar('\t');
		do {
			ch = *cp++;
			putchar(ch);
		} while (ch != '\n' &&
			 cp < sb->final_buf + sb->final_buf_size);
	}

	if (sb->final_buf_size && cp[-1] != '\n')
		putchar('\n');
}
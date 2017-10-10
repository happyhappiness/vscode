#define OUTPUT_SHOW_NUMBER	040
#define OUTPUT_SHOW_SCORE      0100
#define OUTPUT_NO_AUTHOR       0200
#define OUTPUT_SHOW_EMAIL	0400
#define OUTPUT_LINE_PORCELAIN 01000

static void emit_porcelain_details(struct blame_origin *suspect, int repeat)
{
	if (emit_one_suspect_detail(suspect, repeat) ||
	    (suspect->commit->object.flags & MORE_THAN_ONE_PATH))
		write_filename_info(suspect);
}

static void emit_porcelain(struct blame_scoreboard *sb, struct blame_entry *ent,
			   int opt)
{
	int repeat = opt & OUTPUT_LINE_PORCELAIN;
	int cnt;
	const char *cp;
	struct blame_origin *suspect = ent->suspect;
	char hex[GIT_MAX_HEXSZ + 1];

	oid_to_hex_r(hex, &suspect->commit->object.oid);
	printf("%s %d %d %d\n",
	       hex,
	       ent->s_lno + 1,
	       ent->lno + 1,
	       ent->num_lines);
	emit_porcelain_details(suspect, repeat);

	cp = blame_nth_line(sb, ent->lno);
	for (cnt = 0; cnt < ent->num_lines; cnt++) {
		char ch;
		if (cnt) {
			printf("%s %d %d\n", hex,
			       ent->s_lno + 1 + cnt,
			       ent->lno + 1 + cnt);

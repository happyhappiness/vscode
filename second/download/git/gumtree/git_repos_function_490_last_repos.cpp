unsigned blame_entry_score(struct blame_scoreboard *sb, struct blame_entry *e)
{
	unsigned score;
	const char *cp, *ep;

	if (e->score)
		return e->score;

	score = 1;
	cp = blame_nth_line(sb, e->lno);
	ep = blame_nth_line(sb, e->lno + e->num_lines);
	while (cp < ep) {
		unsigned ch = *((unsigned char *)cp);
		if (isalnum(ch))
			score++;
		cp++;
	}
	e->score = score;
	return score;
}
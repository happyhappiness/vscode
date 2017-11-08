static int find_pos(struct apply_state *state,
		    struct image *img,
		    struct image *preimage,
		    struct image *postimage,
		    int line,
		    unsigned ws_rule,
		    int match_beginning, int match_end)
{
	int i;
	unsigned long backwards, forwards, try;
	int backwards_lno, forwards_lno, try_lno;

	/*
	 * If match_beginning or match_end is specified, there is no
	 * point starting from a wrong line that will never match and
	 * wander around and wait for a match at the specified end.
	 */
	if (match_beginning)
		line = 0;
	else if (match_end)
		line = img->nr - preimage->nr;

	/*
	 * Because the comparison is unsigned, the following test
	 * will also take care of a negative line number that can
	 * result when match_end and preimage is larger than the target.
	 */
	if ((size_t) line > img->nr)
		line = img->nr;

	try = 0;
	for (i = 0; i < line; i++)
		try += img->line[i].len;

	/*
	 * There's probably some smart way to do this, but I'll leave
	 * that to the smart and beautiful people. I'm simple and stupid.
	 */
	backwards = try;
	backwards_lno = line;
	forwards = try;
	forwards_lno = line;
	try_lno = line;

	for (i = 0; ; i++) {
		if (match_fragment(state, img, preimage, postimage,
				   try, try_lno, ws_rule,
				   match_beginning, match_end))
			return try_lno;

	again:
		if (backwards_lno == 0 && forwards_lno == img->nr)
			break;

		if (i & 1) {
			if (backwards_lno == 0) {
				i++;
				goto again;
			}
			backwards_lno--;
			backwards -= img->line[backwards_lno].len;
			try = backwards;
			try_lno = backwards_lno;
		} else {
			if (forwards_lno == img->nr) {
				i++;
				goto again;
			}
			forwards += img->line[forwards_lno].len;
			forwards_lno++;
			try = forwards;
			try_lno = forwards_lno;
		}

	}
	return -1;
}
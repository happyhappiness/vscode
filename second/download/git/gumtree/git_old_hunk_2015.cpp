		new += len;
		fixed += len;
		postimage->line[i].len = len;
		ctx++;
	}

	/* Fix the length of the whole thing */
	postimage->len = new - postimage->buf;
	postimage->nr -= reduced;
}

static int match_fragment(struct image *img,

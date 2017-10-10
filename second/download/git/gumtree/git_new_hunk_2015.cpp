		new += len;
		fixed += len;
		postimage->line[i].len = len;
		ctx++;
	}

	if (postlen
	    ? postlen < new - postimage->buf
	    : postimage->len < new - postimage->buf)
		die("BUG: caller miscounted postlen: asked %d, orig = %d, used = %d",
		    (int)postlen, (int) postimage->len, (int)(new - postimage->buf));

	/* Fix the length of the whole thing */
	postimage->len = new - postimage->buf;
	postimage->nr -= reduced;
}

static int match_fragment(struct image *img,

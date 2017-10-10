		die("internal error in merge #3");
	if (!DIFF_FILE_VALID(c->two))
		die("internal error in merge #4");

	dp = diff_queue(outq, d->one, c->two);
	dp->score = p->score;
	diff_free_filespec_data(d->two);
	diff_free_filespec_data(c->one);
	free(d);
	free(c);
}


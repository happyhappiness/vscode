	char *mark = get_revision_mark(revs, commit);
	if (!strlen(mark))
		return;
	fputs(mark, stdout);
	putchar(' ');
}

static struct entry *insert_new(unsigned char *sha1, int pos)
{
	struct entry *new = xcalloc(1, sizeof(struct entry));
	hashcpy(new->old_sha1, sha1);
	memmove(convert + pos + 1, convert + pos, (nr_convert - pos) * sizeof(struct entry *));
	convert[pos] = new;
	nr_convert++;
	if (nr_convert == MAXOBJECTS)
		die("you're kidding me - hit maximum object limit");
	return new;
}
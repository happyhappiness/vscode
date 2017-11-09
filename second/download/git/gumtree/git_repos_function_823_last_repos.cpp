const unsigned char *do_lookup_replace_object(const unsigned char *sha1)
{
	int pos, depth = MAXREPLACEDEPTH;
	const unsigned char *cur = sha1;

	prepare_replace_object();

	/* Try to recursively replace the object */
	do {
		if (--depth < 0)
			die("replace depth too high for object %s",
			    sha1_to_hex(sha1));

		pos = replace_object_pos(cur);
		if (0 <= pos)
			cur = replace_object[pos]->replacement;
	} while (0 <= pos);

	return cur;
}
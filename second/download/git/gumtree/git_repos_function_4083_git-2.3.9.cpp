static int update_auto_abbrev(int auto_abbrev, struct origin *suspect)
{
	const char *uniq = find_unique_abbrev(suspect->commit->object.sha1,
					      auto_abbrev);
	int len = strlen(uniq);
	if (auto_abbrev < len)
		return len;
	return auto_abbrev;
}
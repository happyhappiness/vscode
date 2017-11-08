static uintmax_t change_note_fanout(struct tree_entry *root,
		unsigned char fanout)
{
	/*
	 * The size of path is due to one slash between every two hex digits,
	 * plus the terminating NUL.  Note that there is no slash at the end, so
	 * the number of slashes is one less than half the number of hex
	 * characters.
	 */
	char hex_oid[GIT_MAX_HEXSZ], path[GIT_MAX_HEXSZ + (GIT_MAX_HEXSZ / 2) - 1 + 1];
	return do_change_note_fanout(root, root, hex_oid, 0, path, 0, fanout);
}
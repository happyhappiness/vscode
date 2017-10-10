 * may have changes in multiple paths. So this needs to appear each time
 * we mention a new group.
 *
 * To allow LF and other nonportable characters in pathnames,
 * they are c-style quoted as needed.
 */
static void write_filename_info(struct blame_origin *suspect)
{
	if (suspect->previous) {
		struct blame_origin *prev = suspect->previous;
		printf("previous %s ", oid_to_hex(&prev->commit->object.oid));
		write_name_quoted(prev->path, stdout, '\n');
	}
	printf("filename ");
	write_name_quoted(suspect->path, stdout, '\n');
}

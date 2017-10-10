 * Add a path to a buffer, converting a relative path to an
 * absolute one in the process.  Symbolic links are not
 * resolved.
 */
extern void strbuf_add_absolute_path(struct strbuf *sb, const char *path);


/**
 * Normalize in-place the path contained in the strbuf. See
 * normalize_path_copy() for details. If an error occurs, the contents of "sb"
 * are left untouched, and -1 is returned.
 */

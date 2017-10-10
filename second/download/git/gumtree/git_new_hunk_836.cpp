 * Add a path to a buffer, converting a relative path to an
 * absolute one in the process.  Symbolic links are not
 * resolved.
 */
extern void strbuf_add_absolute_path(struct strbuf *sb, const char *path);

/**
 * Canonize `path` (make it absolute, resolve symlinks, remove extra
 * slashes) and append it to `sb`.  Die with an informative error
 * message if there is a problem.
 *
 * The directory part of `path` (i.e., everything up to the last
 * dir_sep) must denote a valid, existing directory, but the last
 * component need not exist.
 *
 * Callers that don't mind links should use the more lightweight
 * strbuf_add_absolute_path() instead.
 */
extern void strbuf_add_real_path(struct strbuf *sb, const char *path);


/**
 * Normalize in-place the path contained in the strbuf. See
 * normalize_path_copy() for details. If an error occurs, the contents of "sb"
 * are left untouched, and -1 is returned.
 */

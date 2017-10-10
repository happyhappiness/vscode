 * input, so it is safe to pass this function an arbitrary
 * null-terminated string.
 */
extern int get_sha1_hex(const char *hex, unsigned char *sha1);
extern int get_oid_hex(const char *hex, struct object_id *sha1);

/*
 * Convert a binary sha1 to its hex equivalent. The `_r` variant is reentrant,
 * and writes the NUL-terminated output to the buffer `out`, which must be at
 * least `GIT_SHA1_HEXSZ + 1` bytes, and returns a pointer to out for
 * convenience.
 *
 * The non-`_r` variant returns a static buffer, but uses a ring of 4
 * buffers, making it safe to make multiple calls for a single statement, like:
 *
 *   printf("%s -> %s", sha1_to_hex(one), sha1_to_hex(two));
 */
extern char *sha1_to_hex_r(char *out, const unsigned char *sha1);
extern char *sha1_to_hex(const unsigned char *sha1);	/* static buffer result! */
extern char *oid_to_hex(const struct object_id *oid);	/* same static buffer as sha1_to_hex */

extern int interpret_branch_name(const char *str, int len, struct strbuf *);
extern int get_sha1_mb(const char *str, unsigned char *sha1);


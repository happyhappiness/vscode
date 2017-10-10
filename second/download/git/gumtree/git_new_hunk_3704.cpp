 * The non-`_r` variant returns a static buffer, but uses a ring of 4
 * buffers, making it safe to make multiple calls for a single statement, like:
 *
 *   printf("%s -> %s", sha1_to_hex(one), sha1_to_hex(two));
 */
extern char *sha1_to_hex_r(char *out, const unsigned char *sha1);
extern char *oid_to_hex_r(char *out, const struct object_id *oid);
extern char *sha1_to_hex(const unsigned char *sha1);	/* static buffer result! */
extern char *oid_to_hex(const struct object_id *oid);	/* same static buffer as sha1_to_hex */

extern int interpret_branch_name(const char *str, int len, struct strbuf *);
extern int get_sha1_mb(const char *str, unsigned char *sha1);


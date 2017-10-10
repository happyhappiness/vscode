  * - sha1     - Partial SHA1 value is written here
  * - sha1_len - Max #bytes to store in sha1, Must be >= hex_len / 2, and < 20
  * Returns -1 on error (invalid arguments or invalid SHA1 (not in hex format)).
  * Otherwise, returns number of bytes written to sha1 (i.e. hex_len / 2).
  * Pads sha1 with NULs up to sha1_len (not included in returned length).
  */
-static int get_sha1_hex_segment(const char *hex, unsigned int hex_len,
-		unsigned char *sha1, unsigned int sha1_len)
+static int get_oid_hex_segment(const char *hex, unsigned int hex_len,
+		unsigned char *oid, unsigned int oid_len)
 {
 	unsigned int i, len = hex_len >> 1;
-	if (hex_len % 2 != 0 || len > sha1_len)
+	if (hex_len % 2 != 0 || len > oid_len)
 		return -1;
 	for (i = 0; i < len; i++) {
 		unsigned int val = (hexval(hex[0]) << 4) | hexval(hex[1]);
 		if (val & ~0xff)
 			return -1;
-		*sha1++ = val;
+		*oid++ = val;
 		hex += 2;
 	}
-	for (; i < sha1_len; i++)
-		*sha1++ = 0;
+	for (; i < oid_len; i++)
+		*oid++ = 0;
 	return len;
 }
 
 static int non_note_cmp(const struct non_note *a, const struct non_note *b)
 {
 	return strcmp(a->path, b->path);

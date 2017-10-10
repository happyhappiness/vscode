 {
 	if (len > (size_t) len)
 		die("Cannot handle files this big");
 	return (size_t)len;
 }
 
-static inline int has_extension(const char *filename, const char *ext)
-{
-	size_t len = strlen(filename);
-	size_t extlen = strlen(ext);
-	return len > extlen && !memcmp(filename + len - extlen, ext, extlen);
-}
-
 /* in ctype.c, for kwset users */
 extern const char tolower_trans_tbl[256];
 
 /* Sane ctype - no locale, and works with signed chars */
 #undef isascii
 #undef isspace

 		die_errno("Unable to create temporary file '%s'",
 			nonrelative_template);
 	}
 	return fd;
 }
 
-/* git_mkstemp() - create tmp file honoring TMPDIR variable */
-int git_mkstemp(char *path, size_t len, const char *template)
-{
-	const char *tmp;
-	size_t n;
-
-	tmp = getenv("TMPDIR");
-	if (!tmp)
-		tmp = "/tmp";
-	n = snprintf(path, len, "%s/%s", tmp, template);
-	if (len <= n) {
-		errno = ENAMETOOLONG;
-		return -1;
-	}
-	return mkstemp(path);
-}
-
 /* Adapted from libiberty's mkstemp.c. */
 
 #undef TMP_MAX
 #define TMP_MAX 16384
 
 int git_mkstemps_mode(char *pattern, int suffix_len, int mode)

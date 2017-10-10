  *
  * store_key - pointer to char* which will hold a copy of the key with
  *             lowercase section and variable name
  * baselen - pointer to int which will hold the length of the
  *           section + subsection part, can be NULL
  */
-int git_config_parse_key(const char *key, char **store_key, int *baselen_)
+static int git_config_parse_key_1(const char *key, char **store_key, int *baselen_, int quiet)
 {
 	int i, dot, baselen;
 	const char *last_dot = strrchr(key, '.');
 
 	/*
 	 * Since "key" actually contains the section name and the real
 	 * key name separated by a dot, we have to know where the dot is.
 	 */
 
 	if (last_dot == NULL || last_dot == key) {
-		error("key does not contain a section: %s", key);
+		if (!quiet)
+			error("key does not contain a section: %s", key);
 		return -CONFIG_NO_SECTION_OR_NAME;
 	}
 
 	if (!last_dot[1]) {
-		error("key does not contain variable name: %s", key);
+		if (!quiet)
+			error("key does not contain variable name: %s", key);
 		return -CONFIG_NO_SECTION_OR_NAME;
 	}
 
 	baselen = last_dot - key;
 	if (baselen_)
 		*baselen_ = baselen;
 
 	/*
 	 * Validate the key and while at it, lower case it for matching.
 	 */
-	*store_key = xmalloc(strlen(key) + 1);
+	if (store_key)
+		*store_key = xmalloc(strlen(key) + 1);
 
 	dot = 0;
 	for (i = 0; key[i]; i++) {
 		unsigned char c = key[i];
 		if (c == '.')
 			dot = 1;
 		/* Leave the extended basename untouched.. */
 		if (!dot || i > baselen) {
 			if (!iskeychar(c) ||
 			    (i == baselen + 1 && !isalpha(c))) {
-				error("invalid key: %s", key);
+				if (!quiet)
+					error("invalid key: %s", key);
 				goto out_free_ret_1;
 			}
 			c = tolower(c);
 		} else if (c == '\n') {
-			error("invalid key (newline): %s", key);
+			if (!quiet)
+				error("invalid key (newline): %s", key);
 			goto out_free_ret_1;
 		}
-		(*store_key)[i] = c;
+		if (store_key)
+			(*store_key)[i] = c;
 	}
-	(*store_key)[i] = 0;
+	if (store_key)
+		(*store_key)[i] = 0;
 
 	return 0;
 
 out_free_ret_1:
-	free(*store_key);
-	*store_key = NULL;
+	if (store_key) {
+		free(*store_key);
+		*store_key = NULL;
+	}
 	return -CONFIG_INVALID_KEY;
 }
 
+int git_config_parse_key(const char *key, char **store_key, int *baselen)
+{
+	return git_config_parse_key_1(key, store_key, baselen, 0);
+}
+
+int git_config_key_is_valid(const char *key)
+{
+	return !git_config_parse_key_1(key, NULL, NULL, 1);
+}
+
 /*
  * If value==NULL, unset in (remove from) config,
  * if value_regex!=NULL, disregard key/value pairs where value does not match.
  * if value_regex==CONFIG_REGEX_NONE, do not match any existing values
  *     (only add a new one)
  * if multi_replace==0, nothing, or only one matching key/value is replaced,

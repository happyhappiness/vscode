 struct command {
 	struct command *next;
 	const char *error_string;
 	unsigned int skip_update:1,
 		     did_not_exist:1;
 	int index;
-	unsigned char old_sha1[20];
-	unsigned char new_sha1[20];
+	struct object_id old_oid;
+	struct object_id new_oid;
 	char ref_name[FLEX_ARRAY]; /* more */
 };
 
 static void rp_error(const char *err, ...) __attribute__((format (printf, 1, 2)));
 static void rp_warning(const char *err, ...) __attribute__((format (printf, 1, 2)));
 

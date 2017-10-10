 
 static void show_name(const struct object *obj,
 		      const char *caller_name,
 		      int always, int allow_undefined, int name_only)
 {
 	const char *name;
-	const unsigned char *sha1 = obj->sha1;
+	const struct object_id *oid = &obj->oid;
 
 	if (!name_only)
-		printf("%s ", caller_name ? caller_name : sha1_to_hex(sha1));
+		printf("%s ", caller_name ? caller_name : oid_to_hex(oid));
 	name = get_rev_name(obj);
 	if (name)
 		printf("%s\n", name);
 	else if (allow_undefined)
 		printf("undefined\n");
 	else if (always)
-		printf("%s\n", find_unique_abbrev(sha1, DEFAULT_ABBREV));
+		printf("%s\n", find_unique_abbrev(oid->hash, DEFAULT_ABBREV));
 	else
-		die("cannot describe '%s'", sha1_to_hex(sha1));
+		die("cannot describe '%s'", oid_to_hex(oid));
 }
 
 static char const * const name_rev_usage[] = {
 	N_("git name-rev [<options>] <commit>..."),
 	N_("git name-rev [<options>] --all"),
 	N_("git name-rev [<options>] --stdin"),

 		}
 	}
 	free(stack.stack);
 	return contains_test(candidate, want);
 }
 
-static void show_tag_lines(const unsigned char *sha1, int lines)
+static void show_tag_lines(const struct object_id *oid, int lines)
 {
 	int i;
 	unsigned long size;
 	enum object_type type;
 	char *buf, *sp, *eol;
 	size_t len;
 
-	buf = read_sha1_file(sha1, &type, &size);
+	buf = read_sha1_file(oid->hash, &type, &size);
 	if (!buf)
-		die_errno("unable to read object %s", sha1_to_hex(sha1));
+		die_errno("unable to read object %s", oid_to_hex(oid));
 	if (type != OBJ_COMMIT && type != OBJ_TAG)
 		goto free_return;
 	if (!size)
 		die("an empty %s object %s?",
-		    typename(type), sha1_to_hex(sha1));
+		    typename(type), oid_to_hex(oid));
 
 	/* skip header */
 	sp = strstr(buf, "\n\n");
 	if (!sp)
 		goto free_return;
 

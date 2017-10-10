 #include "builtin.h"
 
-static void flush_current_id(int patchlen, unsigned char *id, unsigned char *result)
+static void flush_current_id(int patchlen, struct object_id *id, struct object_id *result)
 {
 	char name[50];
 
 	if (!patchlen)
 		return;
 
-	memcpy(name, sha1_to_hex(id), 41);
-	printf("%s %s\n", sha1_to_hex(result), name);
+	memcpy(name, oid_to_hex(id), GIT_SHA1_HEXSZ + 1);
+	printf("%s %s\n", oid_to_hex(result), name);
 }
 
 static int remove_space(char *line)
 {
 	char *src = line;
 	char *dst = line;

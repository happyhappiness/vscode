 }
 
 static void objreport(struct object *obj, const char *msg_type,
 			const char *err)
 {
 	fprintf(stderr, "%s in %s %s: %s\n",
-		msg_type, typename(obj->type), sha1_to_hex(obj->sha1), err);
+		msg_type, typename(obj->type), oid_to_hex(&obj->oid), err);
 }
 
 static int objerror(struct object *obj, const char *err)
 {
 	errors_found |= ERROR_OBJECT;
 	objreport(obj, "error", err);

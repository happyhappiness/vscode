 	 */
 }
 
 static void check_object(struct object *obj)
 {
 	if (verbose)
-		fprintf(stderr, "Checking %s\n", oid_to_hex(&obj->oid));
+		fprintf(stderr, "Checking %s\n", describe_object(obj));
 
 	if (obj->flags & REACHABLE)
 		check_reachable_object(obj);
 	else
 		check_unreachable_object(obj);
 }

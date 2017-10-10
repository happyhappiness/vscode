 			 * Links refer to objects in another repositories;
 			 * output the SHA-1 verbatim.
 			 */
 			if (no_data || S_ISGITLINK(spec->mode))
 				printf("M %06o %s ", spec->mode,
 				       sha1_to_hex(anonymize ?
-						   anonymize_sha1(spec->oid.hash) :
+						   anonymize_sha1(&spec->oid) :
 						   spec->oid.hash));
 			else {
 				struct object *object = lookup_object(spec->oid.hash);
 				printf("M %06o :%d ", spec->mode,
 				       get_object_mark(object));
 			}

 			add_object_entry(o->oid.hash, o->type, "", 0);
 		}
 	}
 	free(in_pack.array);
 }
 
-static int add_loose_object(const unsigned char *sha1, const char *path,
+static int add_loose_object(const struct object_id *oid, const char *path,
 			    void *data)
 {
-	enum object_type type = sha1_object_info(sha1, NULL);
+	enum object_type type = sha1_object_info(oid->hash, NULL);
 
 	if (type < 0) {
 		warning("loose object at %s could not be examined", path);
 		return 0;
 	}
 
-	add_object_entry(sha1, type, "", 0);
+	add_object_entry(oid->hash, type, "", 0);
 	return 0;
 }
 
 /*
  * We actually don't even have to worry about reachability here.
  * add_object_entry will weed out duplicates, so we just add every

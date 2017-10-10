 }
 
 static struct ref_entry *create_ref_entry(const char *refname,
 					  const unsigned char *sha1, int flag,
 					  int check_name)
 {
-	int len;
 	struct ref_entry *ref;
 
 	if (check_name &&
 	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
 		die("Reference has invalid format: '%s'", refname);
-	len = strlen(refname) + 1;
-	ref = xmalloc(sizeof(struct ref_entry) + len);
+	FLEX_ALLOC_STR(ref, name, refname);
 	hashcpy(ref->u.value.oid.hash, sha1);
 	oidclr(&ref->u.value.peeled);
-	memcpy(ref->name, refname, len);
 	ref->flag = flag;
 	return ref;
 }
 
 static void clear_ref_dir(struct ref_dir *dir);
 

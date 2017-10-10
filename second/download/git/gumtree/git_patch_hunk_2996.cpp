 
 	do {
 		const char *p;
 		if (skip_prefix(buf->buf, "fetch ", &p)) {
 			const char *name;
 			struct ref *ref;
-			unsigned char old_sha1[20];
+			struct object_id old_oid;
 
-			if (strlen(p) < 40 || get_sha1_hex(p, old_sha1))
+			if (get_oid_hex(p, &old_oid))
 				die("protocol error: expected sha/ref, got %s'", p);
-			if (p[40] == ' ')
-				name = p + 41;
-			else if (!p[40])
+			if (p[GIT_SHA1_HEXSZ] == ' ')
+				name = p + GIT_SHA1_HEXSZ + 1;
+			else if (!p[GIT_SHA1_HEXSZ])
 				name = "";
 			else
 				die("protocol error: expected sha/ref, got %s'", p);
 
 			ref = alloc_ref(name);
-			hashcpy(ref->old_sha1, old_sha1);
+			oidcpy(&ref->old_oid, &old_oid);
 
 			*list = ref;
 			list = &ref->next;
 
 			ALLOC_GROW(to_fetch, nr_heads + 1, alloc_heads);
 			to_fetch[nr_heads++] = ref;

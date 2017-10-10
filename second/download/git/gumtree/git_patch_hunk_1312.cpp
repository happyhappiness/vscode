 	int forty = 0;
 	char *p_start;
 	for (p_start = p; *p; p++) {
 #define ishex(x) (isdigit((x)) || ((x) >= 'a' && (x) <= 'f'))
 		if (!ishex(*p))
 			forty = 0;
-		else if (++forty == 40 &&
+		else if (++forty == GIT_SHA1_HEXSZ &&
 			 !ishex(*(p+1))) {
-			unsigned char sha1[40];
+			struct object_id oid;
 			const char *name = NULL;
 			char c = *(p+1);
 			int p_len = p - p_start + 1;
 
 			forty = 0;
 
 			*(p+1) = 0;
-			if (!get_sha1(p - 39, sha1)) {
+			if (!get_oid(p - (GIT_SHA1_HEXSZ - 1), &oid)) {
 				struct object *o =
-					lookup_object(sha1);
+					lookup_object(oid.hash);
 				if (o)
 					name = get_rev_name(o, &buf);
 			}
 			*(p+1) = c;
 
 			if (!name)
 				continue;
 
 			if (data->name_only)
-				printf("%.*s%s", p_len - 40, p_start, name);
+				printf("%.*s%s", p_len - GIT_SHA1_HEXSZ, p_start, name);
 			else
 				printf("%.*s (%s)", p_len, p_start, name);
 			p_start = p + 1;
 		}
 	}
 

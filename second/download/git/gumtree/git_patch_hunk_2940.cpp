 			ls->dentry_name, repo->url);
 		aborted = 1;
 		free(ref);
 		return;
 	}
 
-	o = parse_object(ref->old_sha1);
+	o = parse_object(ref->old_oid.hash);
 	if (!o) {
 		fprintf(stderr,
 			"Unable to parse object %s for remote ref %s\n",
-			sha1_to_hex(ref->old_sha1), ls->dentry_name);
+			oid_to_hex(&ref->old_oid), ls->dentry_name);
 		aborted = 1;
 		free(ref);
 		return;
 	}
 
-	len = strlen(ls->dentry_name) + 42;
-	ref_info = xcalloc(len + 1, 1);
-	sprintf(ref_info, "%s	%s\n",
-		sha1_to_hex(ref->old_sha1), ls->dentry_name);
-	fwrite_buffer(ref_info, 1, len, buf);
-	free(ref_info);
+	strbuf_addf(buf, "%s\t%s\n",
+		    oid_to_hex(&ref->old_oid), ls->dentry_name);
 
 	if (o->type == OBJ_TAG) {
 		o = deref_tag(o, ls->dentry_name, 0);
-		if (o) {
-			len = strlen(ls->dentry_name) + 45;
-			ref_info = xcalloc(len + 1, 1);
-			sprintf(ref_info, "%s	%s^{}\n",
-				sha1_to_hex(o->sha1), ls->dentry_name);
-			fwrite_buffer(ref_info, 1, len, buf);
-			free(ref_info);
-		}
+		if (o)
+			strbuf_addf(buf, "%s\t%s^{}\n",
+				    oid_to_hex(&o->oid), ls->dentry_name);
 	}
 	free(ref);
 }
 
 static void update_remote_info_refs(struct remote_lock *lock)
 {

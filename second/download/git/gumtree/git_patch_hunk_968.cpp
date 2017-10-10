 		warning(_("the original commit '%s' has a gpg signature."), old_ref);
 		warning(_("the signature will be removed in the replacement commit!"));
 	}
 
 	check_mergetags(commit, argc, argv);
 
-	if (write_sha1_file(buf.buf, buf.len, commit_type, new))
+	if (write_sha1_file(buf.buf, buf.len, commit_type, new.hash))
 		die(_("could not write replacement commit for: '%s'"), old_ref);
 
 	strbuf_release(&buf);
 
-	if (!hashcmp(old, new))
-		return error("new commit is the same as the old one: '%s'", sha1_to_hex(old));
+	if (!oidcmp(&old, &new))
+		return error("new commit is the same as the old one: '%s'", oid_to_hex(&old));
 
-	return replace_object_sha1(old_ref, old, "replacement", new, force);
+	return replace_object_oid(old_ref, &old, "replacement", &new, force);
 }
 
 int cmd_replace(int argc, const char **argv, const char *prefix)
 {
 	int force = 0;
 	int raw = 0;

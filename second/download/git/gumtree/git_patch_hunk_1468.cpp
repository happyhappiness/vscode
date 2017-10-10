 			return 0;
 		if (get_oid_hex(refname + strlen(git_replace_ref_base),
 				&original_oid)) {
 			warning("invalid replace ref %s", refname);
 			return 0;
 		}
-		obj = parse_object(original_oid.hash);
+		obj = parse_object(&original_oid);
 		if (obj)
 			add_name_decoration(DECORATION_GRAFTED, "replaced", obj);
 		return 0;
 	}
 
-	obj = parse_object(oid->hash);
+	obj = parse_object(oid);
 	if (!obj)
 		return 0;
 
 	if (starts_with(refname, "refs/heads/"))
 		type = DECORATION_REF_LOCAL;
 	else if (starts_with(refname, "refs/remotes/"))

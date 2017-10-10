 					  oid.hash, &oc)) {
 			if (seen_dashdash)
 				die(_("unable to resolve revision: %s"), arg);
 			break;
 		}
 
-		object = parse_object_or_die(oid.hash, arg);
+		object = parse_object_or_die(&oid, arg);
 		if (!seen_dashdash)
 			verify_non_filename(prefix, arg);
 		add_object_array_with_path(object, arg, &list, oc.mode, oc.path);
 		free(oc.path);
 	}
 

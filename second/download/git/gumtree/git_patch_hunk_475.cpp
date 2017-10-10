 		const unsigned char *remote = ref->old_oid.hash;
 		struct object *o;
 
 		o = lookup_object(remote);
 		if (!o || !(o->flags & COMPLETE)) {
 			retval = 0;
-			if (!args->verbose)
-				continue;
-			fprintf(stderr,
-				"want %s (%s)\n", sha1_to_hex(remote),
-				ref->name);
+			print_verbose(args, "want %s (%s)", sha1_to_hex(remote),
+				      ref->name);
 			continue;
 		}
-		if (!args->verbose)
-			continue;
-		fprintf(stderr,
-			"already have %s (%s)\n", sha1_to_hex(remote),
-			ref->name);
+		print_verbose(args, _("already have %s (%s)"), sha1_to_hex(remote),
+			      ref->name);
 	}
 	return retval;
 }
 
 static int sideband_demux(int in, int out, void *data)
 {

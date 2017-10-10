 				if (helper_status)
 					printf("error %s non-fast forward\n", ref->name);
 				rc = -2;
 				continue;
 			}
 		}
-		hashcpy(ref->new_sha1, ref->peer_ref->new_sha1);
+		oidcpy(&ref->new_oid, &ref->peer_ref->new_oid);
 		new_refs++;
-		strcpy(old_hex, sha1_to_hex(ref->old_sha1));
-		new_hex = sha1_to_hex(ref->new_sha1);
 
 		fprintf(stderr, "updating '%s'", ref->name);
 		if (strcmp(ref->name, ref->peer_ref->name))
 			fprintf(stderr, " using '%s'", ref->peer_ref->name);
-		fprintf(stderr, "\n  from %s\n  to   %s\n", old_hex, new_hex);
+		fprintf(stderr, "\n  from %s\n  to   %s\n",
+			oid_to_hex(&ref->old_oid), oid_to_hex(&ref->new_oid));
 		if (dry_run) {
 			if (helper_status)
 				printf("ok %s\n", ref->name);
 			continue;
 		}
 

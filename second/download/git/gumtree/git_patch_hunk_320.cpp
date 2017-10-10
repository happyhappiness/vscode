 		switch (p->status) {
 		default:
 			die("internal error in blame::find_origin (%c)",
 			    p->status);
 		case 'M':
 			porigin = get_origin(sb, parent, origin->path);
-			hashcpy(porigin->blob_sha1, p->one->oid.hash);
+			oidcpy(&porigin->blob_oid, &p->one->oid);
 			porigin->mode = p->one->mode;
 			break;
 		case 'A':
 		case 'T':
 			/* Did not exist in parent, or type changed */
 			break;

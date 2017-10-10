 		if (len == GIT_SHA1_HEXSZ + strlen("shallow ") &&
 			skip_prefix(buffer, "shallow ", &arg)) {
 			if (get_oid_hex(arg, &old_oid))
 				die("protocol error: expected shallow sha-1, got '%s'", arg);
 			if (!shallow_points)
 				die("repository on the other end cannot be shallow");
-			sha1_array_append(shallow_points, old_oid.hash);
+			oid_array_append(shallow_points, &old_oid);
 			continue;
 		}
 
 		if (len < GIT_SHA1_HEXSZ + 2 || get_oid_hex(buffer, &old_oid) ||
 			buffer[GIT_SHA1_HEXSZ] != ' ')
 			die("protocol error: expected sha/ref, got '%s'", buffer);

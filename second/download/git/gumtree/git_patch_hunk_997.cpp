 		if (len != name_len + GIT_SHA1_HEXSZ + 1) {
 			free(server_capabilities);
 			server_capabilities = xstrdup(name + name_len + 1);
 		}
 
 		if (extra_have && !strcmp(name, ".have")) {
-			sha1_array_append(extra_have, old_oid.hash);
+			oid_array_append(extra_have, &old_oid);
 			continue;
 		}
 
 		if (!strcmp(name, "capabilities^{}")) {
 			if (saw_response)
 				die("protocol error: unexpected capabilities^{}");

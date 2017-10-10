 		 */
 		if (!memcmp("@@ -", line, 4)) {
 			struct fragment dummy;
 			if (parse_fragment_header(line, len, &dummy) < 0)
 				continue;
 			die(_("patch fragment without header at line %d: %.*s"),
-			    linenr, (int)len-1, line);
+			    state->linenr, (int)len-1, line);
 		}
 
 		if (size < len + 6)
 			break;
 
 		/*
 		 * Git patch? It might not have a real patch, just a rename
 		 * or mode change, so we handle that specially
 		 */
 		if (!memcmp("diff --git ", line, 11)) {
-			int git_hdr_len = parse_git_header(line, len, size, patch);
+			int git_hdr_len = parse_git_header(state, line, len, size, patch);
 			if (git_hdr_len <= len)
 				continue;
 			if (!patch->old_name && !patch->new_name) {
 				if (!patch->def_name)
 					die(Q_("git diff header lacks filename information when removing "
 					       "%d leading pathname component (line %d)",
 					       "git diff header lacks filename information when removing "
 					       "%d leading pathname components (line %d)",
-					       p_value),
-					    p_value, linenr);
+					       state->p_value),
+					    state->p_value, state->linenr);
 				patch->old_name = xstrdup(patch->def_name);
 				patch->new_name = xstrdup(patch->def_name);
 			}
 			if (!patch->is_delete && !patch->new_name)
 				die("git diff header lacks filename information "
-				    "(line %d)", linenr);
+				    "(line %d)", state->linenr);
 			patch->is_toplevel_relative = 1;
 			*hdrsize = git_hdr_len;
 			return offset;
 		}
 
 		/* --- followed by +++ ? */

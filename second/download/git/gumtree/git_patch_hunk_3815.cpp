 		if (one_filesystem) {
 			dev_t parent_device = get_device_or_die("..", cwd.buf,
 								offset);
 			if (parent_device != current_device) {
 				if (nongit_ok) {
 					if (chdir(cwd.buf))
-						die_errno("Cannot come back to cwd");
+						die_errno(_("Cannot come back to cwd"));
 					*nongit_ok = 1;
 					return NULL;
 				}
 				strbuf_setlen(&cwd, offset);
-				die("Not a git repository (or any parent up to mount point %s)\n"
-				"Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).",
+				die(_("Not a git repository (or any parent up to mount point %s)\n"
+				"Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set)."),
 				    cwd.buf);
 			}
 		}
 		if (chdir("..")) {
 			strbuf_setlen(&cwd, offset);
-			die_errno("Cannot change to '%s/..'", cwd.buf);
+			die_errno(_("Cannot change to '%s/..'"), cwd.buf);
 		}
 		offset = offset_parent;
 	}
 }
 
 const char *setup_git_directory_gently(int *nongit_ok)

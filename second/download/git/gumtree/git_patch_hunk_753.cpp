 	}
 	path = real_path(dir);
 
 cleanup_return:
 	if (return_error_code)
 		*return_error_code = error_code;
-	else if (error_code) {
-		switch (error_code) {
-		case READ_GITFILE_ERR_STAT_FAILED:
-		case READ_GITFILE_ERR_NOT_A_FILE:
-			/* non-fatal; follow return path */
-			break;
-		case READ_GITFILE_ERR_OPEN_FAILED:
-			die_errno("Error opening '%s'", path);
-		case READ_GITFILE_ERR_TOO_LARGE:
-			die("Too large to be a .git file: '%s'", path);
-		case READ_GITFILE_ERR_READ_FAILED:
-			die("Error reading %s", path);
-		case READ_GITFILE_ERR_INVALID_FORMAT:
-			die("Invalid gitfile format: %s", path);
-		case READ_GITFILE_ERR_NO_PATH:
-			die("No path in gitfile: %s", path);
-		case READ_GITFILE_ERR_NOT_A_REPO:
-			die("Not a git repository: %s", dir);
-		default:
-			assert(0);
-		}
-	}
+	else if (error_code)
+		read_gitfile_error_die(error_code, path, dir);
 
 	free(buf);
 	return error_code ? NULL : path;
 }
 
 static const char *setup_explicit_git_dir(const char *gitdirenv,

 		      "Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set)."),
 		    dir.buf);
 	default:
 		die("BUG: unhandled setup_git_directory_1() result");
 	}
 
+	/*
+	 * NEEDSWORK: This was a hack in order to get ls-files and grep to have
+	 * properly formated output when recursing submodules.  Once ls-files
+	 * and grep have been changed to perform this recursing in-process this
+	 * needs to be removed.
+	 */
 	env_prefix = getenv(GIT_TOPLEVEL_PREFIX_ENVIRONMENT);
 	if (env_prefix)
 		prefix = env_prefix;
 
 	if (prefix)
 		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
 	else
 		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);
 
 	startup_info->have_repository = !nongit_ok || !*nongit_ok;
 	startup_info->prefix = prefix;
 
+	/*
+	 * Not all paths through the setup code will call 'set_git_dir()' (which
+	 * directly sets up the environment) so in order to guarantee that the
+	 * environment is in a consistent state after setup, explicitly setup
+	 * the environment if we have a repository.
+	 *
+	 * NEEDSWORK: currently we allow bogus GIT_DIR values to be set in some
+	 * code paths so we also need to explicitly setup the environment if
+	 * the user has set GIT_DIR.  It may be beneficial to disallow bogus
+	 * GIT_DIR values at some point in the future.
+	 */
+	if (startup_info->have_repository || getenv(GIT_DIR_ENVIRONMENT)) {
+		if (!the_repository->gitdir) {
+			const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
+			if (!gitdir)
+				gitdir = DEFAULT_GIT_DIR_ENVIRONMENT;
+			repo_set_gitdir(the_repository, gitdir);
+			setup_git_env();
+		}
+	}
+
 	strbuf_release(&dir);
 	strbuf_release(&gitdir);
 
 	return prefix;
 }
 

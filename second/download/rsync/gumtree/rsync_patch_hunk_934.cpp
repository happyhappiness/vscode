 		 * might be better to always use chroot.
 		 *
 		 * So, perhaps if we can't chroot we should just issue
 		 * a warning, unless a "require chroot" flag is set,
 		 * in which case we fail.
 		 */
-		if (chroot(chroot_path)) {
-			rsyserr(FLOG, errno, "chroot %s failed", chroot_path);
+		if (chroot(module_chdir)) {
+			rsyserr(FLOG, errno, "chroot %s failed", module_chdir);
 			io_printf(f_out, "@ERROR: chroot failed\n");
 			return -1;
 		}
-		if (!change_dir(module_dir, CD_NORMAL))
-			goto chdir_failed;
-		if (module_dirlen)
-			sanitize_paths = 1;
-	} else {
-		if (!change_dir(module_dir, CD_NORMAL)) {
-		  chdir_failed:
-			rsyserr(FLOG, errno, "chdir %s failed\n", module_dir);
-			io_printf(f_out, "@ERROR: chdir failed\n");
-			return -1;
-		}
-		sanitize_paths = 1;
+		module_chdir = module_dir;
 	}
 
+	if (!change_dir(module_chdir, CD_NORMAL))
+		return path_failure(f_out, module_chdir, True);
+	if (module_dirlen || !use_chroot)
+		sanitize_paths = 1;
+
 	if ((munge_symlinks = lp_munge_symlinks(i)) < 0)
 		munge_symlinks = !use_chroot || module_dirlen;
 	if (munge_symlinks) {
 		STRUCT_STAT st;
 		if (do_stat(SYMLINK_PREFIX, &st) == 0 && S_ISDIR(st.st_mode)) {
 			rprintf(FLOG, "Symlink munging is unsupported when a %s directory exists.\n",

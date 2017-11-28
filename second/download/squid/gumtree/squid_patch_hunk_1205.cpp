     const int rockDirs = Config.cacheSwap.n_strands;
 
     const bool needCoord = Config.workers > 1 || rockDirs > 0;
     return (needCoord ? 1 : 0) + Config.workers + rockDirs;
 }
 
-String
+SBuf
 ProcessRoles()
 {
-    String roles = "";
+    SBuf roles;
     if (IamMasterProcess())
         roles.append(" master");
     if (IamCoordinatorProcess())
         roles.append(" coordinator");
     if (IamWorkerProcess())
         roles.append(" worker");
     if (IamDiskProcess())
         roles.append(" disker");
     return roles;
 }
 
-void
-writePidFile(void)
-{
-    int fd;
-    const char *f = NULL;
-    mode_t old_umask;
-    char buf[32];
-
-    if (!IamPrimaryProcess())
-        return;
-
-    if ((f = Config.pidFilename) == NULL)
-        return;
-
-    if (!strcmp(Config.pidFilename, "none"))
-        return;
-
-    enter_suid();
-
-    old_umask = umask(022);
-
-    fd = file_open(f, O_WRONLY | O_CREAT | O_TRUNC | O_TEXT);
-
-    umask(old_umask);
-
-    leave_suid();
-
-    if (fd < 0) {
-        debugs(50, DBG_CRITICAL, "" << f << ": " << xstrerror());
-        debug_trap("Could not write pid file");
-        return;
-    }
-
-    snprintf(buf, 32, "%d\n", (int) getpid());
-    FD_WRITE_METHOD(fd, buf, strlen(buf));
-    file_close(fd);
-}
-
-pid_t
-readPidFile(void)
-{
-    FILE *pid_fp = NULL;
-    const char *f = Config.pidFilename;
-    char *chroot_f = NULL;
-    pid_t pid = -1;
-    int i;
-
-    if (f == NULL || !strcmp(Config.pidFilename, "none")) {
-        fprintf(stderr, APP_SHORTNAME ": ERROR: No pid file name defined\n");
-        exit(1);
-    }
-
-    if (Config.chroot_dir && geteuid() == 0) {
-        int len = strlen(Config.chroot_dir) + 1 + strlen(f) + 1;
-        chroot_f = (char *)xmalloc(strlen(Config.chroot_dir) + 1 + strlen(f) + 1);
-        snprintf(chroot_f, len, "%s/%s", Config.chroot_dir, f);
-        f = chroot_f;
-    }
-
-    pid_fp = fopen(f, "r");
-
-    if (pid_fp != NULL) {
-        pid = 0;
-
-        if (fscanf(pid_fp, "%d", &i) == 1)
-            pid = (pid_t) i;
-
-        fclose(pid_fp);
-    } else {
-        if (errno != ENOENT) {
-            fprintf(stderr, APP_SHORTNAME ": ERROR: Could not read pid file\n");
-            fprintf(stderr, "\t%s: %s\n", f, xstrerror());
-            exit(1);
-        }
-    }
-
-    safe_free(chroot_f);
-    return pid;
-}
-
 /* A little piece of glue for odd systems */
 #ifndef RLIMIT_NOFILE
 #ifdef RLIMIT_OFILE
 #define RLIMIT_NOFILE RLIMIT_OFILE
 #endif
 #endif

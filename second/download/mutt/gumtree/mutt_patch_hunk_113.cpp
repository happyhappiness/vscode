 static sigset_t SigsetSys;
 static struct sigaction SysOldInt;
 static struct sigaction SysOldQuit;
 static int IsEndwin = 0;
 
 /* Attempt to catch "ordinary" signals and shut down gracefully. */
-RETSIGTYPE exit_handler (int sig)
+static void exit_handler (int sig)
 {
   curs_set (1);
   endwin (); /* just to be safe */
 #if SYS_SIGLIST_DECLARED
   printf(_("%s...  Exiting.\n"), sys_siglist[sig]);
 #else

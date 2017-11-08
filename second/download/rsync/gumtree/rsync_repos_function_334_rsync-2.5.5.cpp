static RETSIGTYPE sigchld_handler(int UNUSED(val)) {
#ifdef WNOHANG
	while (waitpid(-1, NULL, WNOHANG) > 0) ;
#endif
}
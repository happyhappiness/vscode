void send_exclude_list(int f)
{
	int i;
	extern int remote_version;

	if (!exclude_list) {
		write_int(f,0);
		return;
	}

	for (i=0;exclude_list[i];i++) {
		char *pattern = exclude_list[i]->orig; 
		int l;

		if (remote_version < 19) {
			if (strncmp(pattern,"+ ", 2)==0) {
				rprintf(FERROR,"remote rsync does not support include syntax - aborting\n");
				exit_cleanup(1);
			}
			
			if (strncmp(pattern,"- ", 2) == 0) {
				pattern += 2;
			}
		}
		
		l = strlen(pattern);
		if (l == 0) continue;
		write_int(f,l);
		write_buf(f,pattern,l);
	}    

	write_int(f,0);
}
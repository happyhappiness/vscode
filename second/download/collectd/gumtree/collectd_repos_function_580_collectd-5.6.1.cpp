static void in_place_replace_sensu_name_reserved(char *orig_name) /* {{{ */
{
	int len=strlen(orig_name);
	for (int i=0; i<len; i++) {
		// some plugins like ipmi generate special characters in metric name
		switch(orig_name[i]) {
			case '(': orig_name[i] = '_'; break;
			case ')': orig_name[i] = '_'; break;
			case ' ': orig_name[i] = '_'; break;
			case '"': orig_name[i] = '_'; break;
			case '\'': orig_name[i] = '_'; break;
			case '+': orig_name[i] = '_'; break;
		}
	}
}
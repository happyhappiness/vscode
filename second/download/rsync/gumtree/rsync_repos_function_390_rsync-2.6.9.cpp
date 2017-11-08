static void read_final_goodbye(int f_in, int f_out)
{
	int i;

	if (protocol_version < 29)
		i = read_int(f_in);
	else {
		while ((i = read_int(f_in)) == the_file_list->count
		    && read_shortint(f_in) == ITEM_IS_NEW) {
			/* Forward the keep-alive (no-op) to the receiver. */
			write_int(f_out, the_file_list->count);
			write_shortint(f_out, ITEM_IS_NEW);
		}
	}

	if (i != -1) {
		rprintf(FERROR, "Invalid packet at end of run (%d) [%s]\n",
			i, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
}
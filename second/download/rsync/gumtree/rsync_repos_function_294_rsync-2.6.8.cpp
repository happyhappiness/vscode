static int get_next_gen_i(int batch_gen_fd, int next_gen_i, int desired_i)
{
	while (next_gen_i < desired_i) {
		if (next_gen_i >= 0) {
			rprintf(FINFO,
				"(No batched update for%s \"%s\")\n",
				phase ? " resend of" : "",
				f_name(the_file_list->files[next_gen_i], NULL));
		}
		next_gen_i = read_int(batch_gen_fd);
		if (next_gen_i == -1)
			next_gen_i = the_file_list->count;
	}
	return next_gen_i;
}
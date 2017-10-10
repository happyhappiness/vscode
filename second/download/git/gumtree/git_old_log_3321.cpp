printf("%s%s@@ -%ld,%ld +%ld,%ld @@%s\n",
		       prefix, c_frag,
		       p_start+1, p_end-p_start, t_start+1, t_end-t_start,
		       c_reset);
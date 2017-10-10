		 * not want the extra blank line.
		 */
		if (!use_stdout)
			rev.shown_one = 0;
		if (shown) {
			if (rev.mime_boundary)
				printf("\n--%s%s--\n\n\n",
				       mime_boundary_leader,
				       rev.mime_boundary);
			else
				print_signature();
			print_bases(&bases);
		}
		if (!use_stdout)
			fclose(stdout);
	}
	free(list);
	free(branch_name);
	string_list_clear(&extra_to, 0);
	string_list_clear(&extra_cc, 0);
	string_list_clear(&extra_hdr, 0);

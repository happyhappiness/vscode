			if (rev.mime_boundary)
				printf("\n--%s%s--\n\n\n",
				       mime_boundary_leader,
				       rev.mime_boundary);
			else
				print_signature();
		}
		if (!use_stdout)
			fclose(stdout);
	}
	free(list);
	free(branch_name);

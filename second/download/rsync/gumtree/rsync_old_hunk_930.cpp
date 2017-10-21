
	if (remove_source_files == 1)
		args[ac++] = "--remove-source-files";
	else if (remove_source_files)
		args[ac++] = "--remove-sent-files";

	*argc_p = ac;
	return;

    oom:
	out_of_memory("server_options");
}

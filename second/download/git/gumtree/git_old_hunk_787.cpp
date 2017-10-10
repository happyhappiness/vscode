	else if (options.verbosity > 1)
		argv_array_push(&args, "--verbose");
	argv_array_push(&args, options.progress ? "--progress" : "--no-progress");
	for_each_string_list_item(cas_option, &cas_options)
		argv_array_push(&args, cas_option->string);
	argv_array_push(&args, url.buf);
	for (i = 0; i < nr_spec; i++)
		argv_array_push(&args, specs[i]);

	memset(&rpc, 0, sizeof(rpc));
	rpc.service_name = "git-receive-pack",
	rpc.argv = args.argv;

	err = rpc_service(&rpc, heads);
	if (rpc.result.len)
		write_or_die(1, rpc.result.buf, rpc.result.len);
	strbuf_release(&rpc.result);
	argv_array_clear(&args);
	return err;
}

static int push(int nr_spec, char **specs)
{

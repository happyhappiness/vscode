	ret = finish_command(&cmd);
	if (!ret || (args->check_self_contained_and_connected && ret == 1))
		args->self_contained_and_connected =
			args->check_self_contained_and_connected &&
			ret == 0;
	else
		die(_("%s failed"), cmd_name);
	if (use_sideband && finish_async(&demux))
		die(_("error in sideband demultiplexer"));
	return 0;
}

static int cmp_ref_by_name(const void *a_, const void *b_)
{
	const struct ref *a = *((const struct ref **)a_);

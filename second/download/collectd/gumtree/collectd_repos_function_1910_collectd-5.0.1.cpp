void
TC_DUMP_ENTRIES(const TC_HANDLE_T handle)
{
	iptc_fn = TC_DUMP_ENTRIES;
	CHECK(handle);

	printf("libiptc v%s. %u bytes.\n",
	       XTABLES_VERSION, handle->entries->size);
	printf("Table `%s'\n", handle->info.name);
	printf("Hooks: pre/in/fwd/out/post = %u/%u/%u/%u/%u\n",
	       handle->info.hook_entry[HOOK_PRE_ROUTING],
	       handle->info.hook_entry[HOOK_LOCAL_IN],
	       handle->info.hook_entry[HOOK_FORWARD],
	       handle->info.hook_entry[HOOK_LOCAL_OUT],
	       handle->info.hook_entry[HOOK_POST_ROUTING]);
	printf("Underflows: pre/in/fwd/out/post = %u/%u/%u/%u/%u\n",
	       handle->info.underflow[HOOK_PRE_ROUTING],
	       handle->info.underflow[HOOK_LOCAL_IN],
	       handle->info.underflow[HOOK_FORWARD],
	       handle->info.underflow[HOOK_LOCAL_OUT],
	       handle->info.underflow[HOOK_POST_ROUTING]);

	ENTRY_ITERATE(handle->entries->entrytable, handle->entries->size,
		      dump_entry, handle);
}
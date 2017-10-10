
		object->flags |= SHOWN;
	}
	fclose(f);
}

int cmd_fast_export(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	struct object_array commits = OBJECT_ARRAY_INIT;
	struct commit *commit;
	char *export_filename = NULL, *import_filename = NULL;
	uint32_t lastimportid;
	struct option options[] = {
		OPT_INTEGER(0, "progress", &progress,
			    N_("show progress after <n> objects")),
		OPT_CALLBACK(0, "signed-tags", &signed_tag_mode, N_("mode"),
			     N_("select handling of signed tags"),
			     parse_opt_signed_tag_mode),

		free_commit_list(commit->parents);
		commit->parents = NULL;
	}
	free_commit_buffer(commit);
}

static void finish_object(struct object *obj, const char *name, void *cb_data)
{
	struct rev_list_info *info = cb_data;
	if (obj->type == OBJ_BLOB && !has_sha1_file(obj->sha1))
		die("missing blob object '%s'", sha1_to_hex(obj->sha1));
	if (info->revs->verify_objects && !obj->parsed && obj->type != OBJ_COMMIT)
		parse_object(obj->sha1);
}

static void show_object(struct object *obj, const char *name, void *cb_data)
{
	struct rev_list_info *info = cb_data;
	finish_object(obj, name, cb_data);
	if (info->flags & REV_LIST_QUIET)
		return;
	show_object_with_name(stdout, obj, name);
}

static void show_edge(struct commit *commit)
{
	printf("-%s\n", sha1_to_hex(commit->object.sha1));
}

static void print_var_str(const char *var, const char *val)
{
	printf("%s='%s'\n", var, val);
}

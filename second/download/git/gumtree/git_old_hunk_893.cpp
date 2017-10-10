		default:
			return error(_("could not create leading directories "
				       "of '%s'"), path);
	}
}

static int run_dir_diff(const char *extcmd, int symlinks, const char *prefix,
			int argc, const char **argv)
{
	char tmpdir[PATH_MAX];
	struct strbuf info = STRBUF_INIT, lpath = STRBUF_INIT;
	struct strbuf rpath = STRBUF_INIT, buf = STRBUF_INIT;
	struct strbuf ldir = STRBUF_INIT, rdir = STRBUF_INIT;
	struct strbuf wtdir = STRBUF_INIT;
	size_t ldir_len, rdir_len, wtdir_len;
	struct cache_entry *ce = xcalloc(1, sizeof(ce) + PATH_MAX + 1);
	const char *workdir, *tmp;
	int ret = 0, i;
	FILE *fp;
	struct hashmap working_tree_dups, submodules, symlinks2;
	struct hashmap_iter iter;
	struct pair_entry *entry;
	enum object_type type;
	unsigned long size;
	struct index_state wtindex;
	struct checkout lstate, rstate;
	int rc, flags = RUN_GIT_CMD, err = 0;
	struct child_process child = CHILD_PROCESS_INIT;
	const char *helper_argv[] = { "difftool--helper", NULL, NULL, NULL };
	struct hashmap wt_modified, tmp_modified;

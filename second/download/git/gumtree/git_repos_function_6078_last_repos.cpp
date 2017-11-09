static int run_dir_diff(const char *extcmd, int symlinks, const char *prefix,
			int argc, const char **argv)
{
	char tmpdir[PATH_MAX];
	struct strbuf info = STRBUF_INIT, lpath = STRBUF_INIT;
	struct strbuf rpath = STRBUF_INIT, buf = STRBUF_INIT;
	struct strbuf ldir = STRBUF_INIT, rdir = STRBUF_INIT;
	struct strbuf wtdir = STRBUF_INIT;
	char *lbase_dir, *rbase_dir;
	size_t ldir_len, rdir_len, wtdir_len;
	const char *workdir, *tmp;
	int ret = 0, i;
	FILE *fp;
	struct hashmap working_tree_dups, submodules, symlinks2;
	struct hashmap_iter iter;
	struct pair_entry *entry;
	struct index_state wtindex;
	struct checkout lstate, rstate;
	int rc, flags = RUN_GIT_CMD, err = 0;
	struct child_process child = CHILD_PROCESS_INIT;
	const char *helper_argv[] = { "difftool--helper", NULL, NULL, NULL };
	struct hashmap wt_modified, tmp_modified;
	int indices_loaded = 0;

	workdir = get_git_work_tree();

	/* Setup temp directories */
	tmp = getenv("TMPDIR");
	xsnprintf(tmpdir, sizeof(tmpdir), "%s/git-difftool.XXXXXX", tmp ? tmp : "/tmp");
	if (!mkdtemp(tmpdir))
		return error("could not create '%s'", tmpdir);
	strbuf_addf(&ldir, "%s/left/", tmpdir);
	strbuf_addf(&rdir, "%s/right/", tmpdir);
	strbuf_addstr(&wtdir, workdir);
	if (!wtdir.len || !is_dir_sep(wtdir.buf[wtdir.len - 1]))
		strbuf_addch(&wtdir, '/');
	mkdir(ldir.buf, 0700);
	mkdir(rdir.buf, 0700);

	memset(&wtindex, 0, sizeof(wtindex));

	memset(&lstate, 0, sizeof(lstate));
	lstate.base_dir = lbase_dir = xstrdup(ldir.buf);
	lstate.base_dir_len = ldir.len;
	lstate.force = 1;
	memset(&rstate, 0, sizeof(rstate));
	rstate.base_dir = rbase_dir = xstrdup(rdir.buf);
	rstate.base_dir_len = rdir.len;
	rstate.force = 1;

	ldir_len = ldir.len;
	rdir_len = rdir.len;
	wtdir_len = wtdir.len;

	hashmap_init(&working_tree_dups,
		     (hashmap_cmp_fn)working_tree_entry_cmp, NULL, 0);
	hashmap_init(&submodules, (hashmap_cmp_fn)pair_cmp, NULL, 0);
	hashmap_init(&symlinks2, (hashmap_cmp_fn)pair_cmp, NULL, 0);

	child.no_stdin = 1;
	child.git_cmd = 1;
	child.use_shell = 0;
	child.clean_on_exit = 1;
	child.dir = prefix;
	child.out = -1;
	argv_array_pushl(&child.args, "diff", "--raw", "--no-abbrev", "-z",
			 NULL);
	for (i = 0; i < argc; i++)
		argv_array_push(&child.args, argv[i]);
	if (start_command(&child))
		die("could not obtain raw diff");
	fp = xfdopen(child.out, "r");

	/* Build index info for left and right sides of the diff */
	i = 0;
	while (!strbuf_getline_nul(&info, fp)) {
		int lmode, rmode;
		struct object_id loid, roid;
		char status;
		const char *src_path, *dst_path;

		if (starts_with(info.buf, "::"))
			die(N_("combined diff formats('-c' and '--cc') are "
			       "not supported in\n"
			       "directory diff mode('-d' and '--dir-diff')."));

		if (parse_index_info(info.buf, &lmode, &rmode, &loid, &roid,
				     &status))
			break;
		if (strbuf_getline_nul(&lpath, fp))
			break;
		src_path = lpath.buf;

		i++;
		if (status != 'C' && status != 'R') {
			dst_path = src_path;
		} else {
			if (strbuf_getline_nul(&rpath, fp))
				break;
			dst_path = rpath.buf;
		}

		if (S_ISGITLINK(lmode) || S_ISGITLINK(rmode)) {
			strbuf_reset(&buf);
			strbuf_addf(&buf, "Subproject commit %s",
				    oid_to_hex(&loid));
			add_left_or_right(&submodules, src_path, buf.buf, 0);
			strbuf_reset(&buf);
			strbuf_addf(&buf, "Subproject commit %s",
				    oid_to_hex(&roid));
			if (!oidcmp(&loid, &roid))
				strbuf_addstr(&buf, "-dirty");
			add_left_or_right(&submodules, dst_path, buf.buf, 1);
			continue;
		}

		if (S_ISLNK(lmode)) {
			char *content = get_symlink(&loid, src_path);
			add_left_or_right(&symlinks2, src_path, content, 0);
			free(content);
		}

		if (S_ISLNK(rmode)) {
			char *content = get_symlink(&roid, dst_path);
			add_left_or_right(&symlinks2, dst_path, content, 1);
			free(content);
		}

		if (lmode && status != 'C') {
			if (checkout_path(lmode, &loid, src_path, &lstate)) {
				ret = error("could not write '%s'", src_path);
				goto finish;
			}
		}

		if (rmode && !S_ISLNK(rmode)) {
			struct working_tree_entry *entry;

			/* Avoid duplicate working_tree entries */
			FLEX_ALLOC_STR(entry, path, dst_path);
			hashmap_entry_init(entry, strhash(dst_path));
			if (hashmap_get(&working_tree_dups, entry, NULL)) {
				free(entry);
				continue;
			}
			hashmap_add(&working_tree_dups, entry);

			if (!use_wt_file(workdir, dst_path, &roid)) {
				if (checkout_path(rmode, &roid, dst_path,
						  &rstate)) {
					ret = error("could not write '%s'",
						    dst_path);
					goto finish;
				}
			} else if (!is_null_oid(&roid)) {
				/*
				 * Changes in the working tree need special
				 * treatment since they are not part of the
				 * index.
				 */
				struct cache_entry *ce2 =
					make_cache_entry(rmode, roid.hash,
							 dst_path, 0, 0);

				add_index_entry(&wtindex, ce2,
						ADD_CACHE_JUST_APPEND);

				add_path(&rdir, rdir_len, dst_path);
				if (ensure_leading_directories(rdir.buf)) {
					ret = error("could not create "
						    "directory for '%s'",
						    dst_path);
					goto finish;
				}
				add_path(&wtdir, wtdir_len, dst_path);
				if (symlinks) {
					if (symlink(wtdir.buf, rdir.buf)) {
						ret = error_errno("could not symlink '%s' to '%s'", wtdir.buf, rdir.buf);
						goto finish;
					}
				} else {
					struct stat st;
					if (stat(wtdir.buf, &st))
						st.st_mode = 0644;
					if (copy_file(rdir.buf, wtdir.buf,
						      st.st_mode)) {
						ret = error("could not copy '%s' to '%s'", wtdir.buf, rdir.buf);
						goto finish;
					}
				}
			}
		}
	}

	fclose(fp);
	fp = NULL;
	if (finish_command(&child)) {
		ret = error("error occurred running diff --raw");
		goto finish;
	}

	if (!i)
		goto finish;

	/*
	 * Changes to submodules require special treatment.This loop writes a
	 * temporary file to both the left and right directories to show the
	 * change in the recorded SHA1 for the submodule.
	 */
	hashmap_iter_init(&submodules, &iter);
	while ((entry = hashmap_iter_next(&iter))) {
		if (*entry->left) {
			add_path(&ldir, ldir_len, entry->path);
			ensure_leading_directories(ldir.buf);
			write_file(ldir.buf, "%s", entry->left);
		}
		if (*entry->right) {
			add_path(&rdir, rdir_len, entry->path);
			ensure_leading_directories(rdir.buf);
			write_file(rdir.buf, "%s", entry->right);
		}
	}

	/*
	 * Symbolic links require special treatment.The standard "git diff"
	 * shows only the link itself, not the contents of the link target.
	 * This loop replicates that behavior.
	 */
	hashmap_iter_init(&symlinks2, &iter);
	while ((entry = hashmap_iter_next(&iter))) {
		if (*entry->left) {
			add_path(&ldir, ldir_len, entry->path);
			ensure_leading_directories(ldir.buf);
			write_file(ldir.buf, "%s", entry->left);
		}
		if (*entry->right) {
			add_path(&rdir, rdir_len, entry->path);
			ensure_leading_directories(rdir.buf);
			write_file(rdir.buf, "%s", entry->right);
		}
	}

	strbuf_release(&buf);

	strbuf_setlen(&ldir, ldir_len);
	helper_argv[1] = ldir.buf;
	strbuf_setlen(&rdir, rdir_len);
	helper_argv[2] = rdir.buf;

	if (extcmd) {
		helper_argv[0] = extcmd;
		flags = 0;
	} else
		setenv("GIT_DIFFTOOL_DIRDIFF", "true", 1);
	rc = run_command_v_opt(helper_argv, flags);

	/*
	 * If the diff includes working copy files and those
	 * files were modified during the diff, then the changes
	 * should be copied back to the working tree.
	 * Do not copy back files when symlinks are used and the
	 * external tool did not replace the original link with a file.
	 *
	 * These hashes are loaded lazily since they aren't needed
	 * in the common case of --symlinks and the difftool updating
	 * files through the symlink.
	 */
	hashmap_init(&wt_modified, (hashmap_cmp_fn)path_entry_cmp,
		     NULL, wtindex.cache_nr);
	hashmap_init(&tmp_modified, (hashmap_cmp_fn)path_entry_cmp,
		     NULL, wtindex.cache_nr);

	for (i = 0; i < wtindex.cache_nr; i++) {
		struct hashmap_entry dummy;
		const char *name = wtindex.cache[i]->name;
		struct stat st;

		add_path(&rdir, rdir_len, name);
		if (lstat(rdir.buf, &st))
			continue;

		if ((symlinks && S_ISLNK(st.st_mode)) || !S_ISREG(st.st_mode))
			continue;

		if (!indices_loaded) {
			static struct lock_file lock;
			strbuf_reset(&buf);
			strbuf_addf(&buf, "%s/wtindex", tmpdir);
			if (hold_lock_file_for_update(&lock, buf.buf, 0) < 0 ||
			    write_locked_index(&wtindex, &lock, COMMIT_LOCK)) {
				ret = error("could not write %s", buf.buf);
				rollback_lock_file(&lock);
				goto finish;
			}
			changed_files(&wt_modified, buf.buf, workdir);
			strbuf_setlen(&rdir, rdir_len);
			changed_files(&tmp_modified, buf.buf, rdir.buf);
			add_path(&rdir, rdir_len, name);
			indices_loaded = 1;
		}

		hashmap_entry_init(&dummy, strhash(name));
		if (hashmap_get(&tmp_modified, &dummy, name)) {
			add_path(&wtdir, wtdir_len, name);
			if (hashmap_get(&wt_modified, &dummy, name)) {
				warning(_("both files modified: '%s' and '%s'."),
					wtdir.buf, rdir.buf);
				warning(_("working tree file has been left."));
				warning("%s", "");
				err = 1;
			} else if (unlink(wtdir.buf) ||
				   copy_file(wtdir.buf, rdir.buf, st.st_mode))
				warning_errno(_("could not copy '%s' to '%s'"),
					      rdir.buf, wtdir.buf);
		}
	}

	if (err) {
		warning(_("temporary files exist in '%s'."), tmpdir);
		warning(_("you may want to cleanup or recover these."));
		exit(1);
	} else
		exit_cleanup(tmpdir, rc);

finish:
	if (fp)
		fclose(fp);

	free(lbase_dir);
	free(rbase_dir);
	strbuf_release(&ldir);
	strbuf_release(&rdir);
	strbuf_release(&wtdir);
	strbuf_release(&buf);

	return ret;
}
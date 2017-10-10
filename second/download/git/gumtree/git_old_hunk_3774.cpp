			 * and/or work tree, but we do not do that now.
			 */
			update_wd = 0;
			goto update_index;
		}

		buf = read_sha1_file(sha, &type, &size);
		if (!buf)
			die(_("cannot read object %s '%s'"), sha1_to_hex(sha), path);
		if (type != OBJ_BLOB)
			die(_("blob expected for %s '%s'"), sha1_to_hex(sha), path);
		if (S_ISREG(mode)) {
			struct strbuf strbuf = STRBUF_INIT;
			if (convert_to_working_tree(path, buf, size, &strbuf)) {
				free(buf);
				size = strbuf.len;
				buf = strbuf_detach(&strbuf, NULL);
			}
		}

		if (make_room_for_path(o, path) < 0) {
			update_wd = 0;
			free(buf);
			goto update_index;
		}
		if (S_ISREG(mode) || (!has_symlinks && S_ISLNK(mode))) {
			int fd;
			if (mode & 0100)
				mode = 0777;
			else
				mode = 0666;
			fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, mode);
			if (fd < 0)
				die_errno(_("failed to open '%s'"), path);
			write_in_full(fd, buf, size);
			close(fd);
		} else if (S_ISLNK(mode)) {
			char *lnk = xmemdupz(buf, size);
			safe_create_leading_directories_const(path);
			unlink(path);
			if (symlink(lnk, path))
				die_errno(_("failed to symlink '%s'"), path);
			free(lnk);
		} else
			die(_("do not know what to do with %06o %s '%s'"),
			    mode, sha1_to_hex(sha), path);
		free(buf);
	}
 update_index:
	if (update_cache)
		add_cacheinfo(mode, sha, path, 0, update_wd, ADD_CACHE_OK_TO_ADD);
}

static void update_file(struct merge_options *o,
			int clean,
			const unsigned char *sha,
			unsigned mode,
			const char *path)
{
	update_file_flags(o, sha, mode, path, o->call_depth || clean, !o->call_depth);
}

/* Low level file merging, update and removal */

struct merge_file_info {
	unsigned char sha[20];
	unsigned mode;
	unsigned clean:1,
		 merge:1;
};

static int merge_3way(struct merge_options *o,

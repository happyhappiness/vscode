	}
	report_helper(list, seen_bits, first, list->nr);
}

static void prepare_packed_git_one(char *objdir, int local)
{
	/* Ensure that this buffer is large enough so that we can
	   append "/pack/" without clobbering the stack even if
	   strlen(objdir) were PATH_MAX.  */
	char path[PATH_MAX + 1 + 4 + 1 + 1];
	int len;
	DIR *dir;
	struct dirent *de;
	struct string_list garbage = STRING_LIST_INIT_DUP;

	sprintf(path, "%s/pack", objdir);
	len = strlen(path);
	dir = opendir(path);
	if (!dir) {
		if (errno != ENOENT)
			error("unable to open object pack directory: %s: %s",
			      path, strerror(errno));
		return;
	}
	path[len++] = '/';
	while ((de = readdir(dir)) != NULL) {
		int namelen = strlen(de->d_name);
		struct packed_git *p;

		if (len + namelen + 1 > sizeof(path)) {
			if (report_garbage) {
				struct strbuf sb = STRBUF_INIT;
				strbuf_addf(&sb, "%.*s/%s", len - 1, path, de->d_name);
				report_garbage("path too long", sb.buf);
				strbuf_release(&sb);
			}
			continue;
		}

		if (is_dot_or_dotdot(de->d_name))
			continue;

		strcpy(path + len, de->d_name);

		if (has_extension(de->d_name, ".idx")) {
			/* Don't reopen a pack we already have. */
			for (p = packed_git; p; p = p->next) {
				if (!memcmp(path, p->pack_name, len + namelen - 4))
					break;
			}
			if (p == NULL &&
			    /*
			     * See if it really is a valid .idx file with
			     * corresponding .pack file that we can map.
			     */
			    (p = add_packed_git(path, len + namelen, local)) != NULL)
				install_packed_git(p);
		}

		if (!report_garbage)
			continue;

		if (has_extension(de->d_name, ".idx") ||
		    has_extension(de->d_name, ".pack") ||
		    has_extension(de->d_name, ".bitmap") ||
		    has_extension(de->d_name, ".keep"))
			string_list_append(&garbage, path);
		else
			report_garbage("garbage found", path);
	}
	closedir(dir);
	report_pack_garbage(&garbage);
	string_list_clear(&garbage, 0);
}

static int sort_pack(const void *a_, const void *b_)
{
	struct packed_git *a = *((struct packed_git **)a_);
	struct packed_git *b = *((struct packed_git **)b_);

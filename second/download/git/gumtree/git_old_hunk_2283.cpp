		strbuf_setlen(&sb, 0);
		strbuf_add(&sb, path, baselen);
		if (!is_directory(sb.buf))
			break;
		if (simplify_away(sb.buf, sb.len, simplify))
			break;
		if (treat_one_path(dir, &sb, simplify,
				   DT_DIR, NULL) == path_none)
			break; /* do not recurse into it */
		if (len <= baselen) {
			rc = 1;
			break; /* finished checking */
		}
	}
	strbuf_release(&sb);
	dir->flags = old_flags;
	return rc;
}

int read_directory(struct dir_struct *dir, const char *path, int len, const struct pathspec *pathspec)
{
	struct path_simplify *simplify;

	/*
	 * Check out create_simplify()
	 */
	if (pathspec)
		GUARD_PATHSPEC(pathspec,

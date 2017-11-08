static void files_reflog_path(struct files_ref_store *refs,
			      struct strbuf *sb,
			      const char *refname)
{
	if (!refname) {
		/*
		 * FIXME: of course this is wrong in multi worktree
		 * setting. To be fixed real soon.
		 */
		strbuf_addf(sb, "%s/logs", refs->gitcommondir);
		return;
	}

	switch (ref_type(refname)) {
	case REF_TYPE_PER_WORKTREE:
	case REF_TYPE_PSEUDOREF:
		strbuf_addf(sb, "%s/logs/%s", refs->gitdir, refname);
		break;
	case REF_TYPE_NORMAL:
		strbuf_addf(sb, "%s/logs/%s", refs->gitcommondir, refname);
		break;
	default:
		die("BUG: unknown ref type %d of ref %s",
		    ref_type(refname), refname);
	}
}
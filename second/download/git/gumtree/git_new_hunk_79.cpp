			} else {
				fprintf(stderr, _("Switched to branch '%s'\n"),
					new->name);
			}
		}
		if (old->path && old->name) {
			if (!ref_exists(old->path) && reflog_exists(old->path))
				delete_reflog(old->path);
		}
	}
	remove_branch_state();
	strbuf_release(&msg);
	if (!opts->quiet &&
	    (new->path || (!opts->force_detach && !strcmp(new->name, "HEAD"))))

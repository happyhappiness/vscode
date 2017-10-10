		if (!d->worktree_status)
			d->worktree_status = p->status;
		d->dirty_submodule = p->two->dirty_submodule;
		if (S_ISGITLINK(p->two->mode))
			d->new_submodule_commits = !!oidcmp(&p->one->oid,
							    &p->two->oid);
	}
}

static int unmerged_mask(const char *path)
{
	int pos, mask;

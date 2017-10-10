	output(o, 1, _("CONFLICT (rename/rename): "
	       "Rename %s->%s in %s. "
	       "Rename %s->%s in %s"),
	       a->path, c1->path, ci->branch1,
	       b->path, c2->path, ci->branch2);

	remove_file(o, 1, a->path, o->call_depth || would_lose_untracked(a->path));
	remove_file(o, 1, b->path, o->call_depth || would_lose_untracked(b->path));

	mfi_c1 = merge_file_special_markers(o, a, c1, &ci->ren1_other,
					    o->branch1, c1->path,
					    o->branch2, ci->ren1_other.path);
	mfi_c2 = merge_file_special_markers(o, b, &ci->ren2_other, c2,
					    o->branch1, ci->ren2_other.path,

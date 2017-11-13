printf(" %s %.*s{%s => %s} (%d%%)\n", renamecopy,
		       (int)(old - p->old_name), p->old_name,
		       old, new, p->score);
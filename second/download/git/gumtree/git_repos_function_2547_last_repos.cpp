static inline void update_tp_entries(struct tree_desc *tp, int nparent)
{
	int i;
	for (i = 0; i < nparent; ++i)
		if (!(tp[i].entry.mode & S_IFXMIN_NEQ))
			update_tree_entry(&tp[i]);
}
static inline int want_ancestry(const struct rev_info *revs)
{
	return (revs->rewrite_parents || revs->children.name);
}
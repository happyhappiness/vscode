static int commit_name_cmp(const struct commit_name *cn1,
		const struct commit_name *cn2, const void *peeled)
{
	return hashcmp(cn1->peeled, peeled ? peeled : cn2->peeled);
}
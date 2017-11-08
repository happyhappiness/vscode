static int commit_name_cmp(const void *unused_cmp_data,
			   const struct commit_name *cn1,
			   const struct commit_name *cn2,
			   const void *peeled)
{
	return oidcmp(&cn1->peeled, peeled ? peeled : &cn2->peeled);
}
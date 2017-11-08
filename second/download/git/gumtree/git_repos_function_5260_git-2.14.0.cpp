static int parse_status_slot(const char *slot)
{
	if (!strcasecmp(slot, "header"))
		return WT_STATUS_HEADER;
	if (!strcasecmp(slot, "branch"))
		return WT_STATUS_ONBRANCH;
	if (!strcasecmp(slot, "updated") || !strcasecmp(slot, "added"))
		return WT_STATUS_UPDATED;
	if (!strcasecmp(slot, "changed"))
		return WT_STATUS_CHANGED;
	if (!strcasecmp(slot, "untracked"))
		return WT_STATUS_UNTRACKED;
	if (!strcasecmp(slot, "nobranch"))
		return WT_STATUS_NOBRANCH;
	if (!strcasecmp(slot, "unmerged"))
		return WT_STATUS_UNMERGED;
	if (!strcasecmp(slot, "localBranch"))
		return WT_STATUS_LOCAL_BRANCH;
	if (!strcasecmp(slot, "remoteBranch"))
		return WT_STATUS_REMOTE_BRANCH;
	return -1;
}
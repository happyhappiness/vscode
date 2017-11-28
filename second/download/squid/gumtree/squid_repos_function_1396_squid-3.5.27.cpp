void storeReplSetup(void)
{
	storeReplAdd("lru", createRemovalPolicy_lru);
}
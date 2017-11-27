static unsigned int iptcc_is_builtin(struct chain_head *c)
{
	return (c->hooknum ? 1 : 0);
}
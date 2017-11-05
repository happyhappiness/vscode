void *nedgetvalue(nedpool **p, void *mem) THROWSPEC
{
	nedpool *np=0;
	mchunkptr mcp=mem2chunk(mem);
	mstate fm;
	if(!(is_aligned(chunk2mem(mcp))) && mcp->head != FENCEPOST_HEAD) return 0;
	if(!cinuse(mcp)) return 0;
	if(!next_pinuse(mcp)) return 0;
	if(!is_mmapped(mcp) && !pinuse(mcp))
	{
		if(next_chunk(prev_chunk(mcp))!=mcp) return 0;
	}
	fm=get_mstate_for(mcp);
	if(!ok_magic(fm)) return 0;
	if(!ok_address(fm, mcp)) return 0;
	if(!fm->extp) return 0;
	np=(nedpool *) fm->extp;
	if(p) *p=np;
	return np->uservalue;
}
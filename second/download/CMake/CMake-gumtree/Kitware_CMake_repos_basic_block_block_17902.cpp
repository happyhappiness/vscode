{
		ret = coder->next.memconfig(coder->next.coder,
				memusage, old_memlimit, new_memlimit);
		assert(*old_memlimit == coder->memlimit);
	}
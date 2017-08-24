{
			// Tell the caller how much memory would have
			// been needed.
			*memlimit = lzma_index_memusage(1, coder.count);
		}
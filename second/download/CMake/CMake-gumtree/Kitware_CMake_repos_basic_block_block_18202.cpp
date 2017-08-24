(opt->lc > LZMA_LCLP_MAX || opt->lp > LZMA_LCLP_MAX
				|| opt->lc + opt->lp > LZMA_LCLP_MAX
				|| opt->pb > LZMA_PB_MAX)
			return LZMA_OPTIONS_ERROR;
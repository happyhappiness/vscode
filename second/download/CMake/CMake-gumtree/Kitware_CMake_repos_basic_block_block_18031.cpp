{
		// We should never get here, but just in case, restore the
		// output position and set the error accordingly if something
		// goes wrong and debugging isn't enabled.
		assert(0);
		*out_pos = out_start;
		ret = LZMA_PROG_ERROR;
	}
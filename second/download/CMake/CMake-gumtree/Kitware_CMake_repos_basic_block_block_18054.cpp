{
				// Let the caller know how much memory would
				// have been needed.
				uint64_t memusage;
				(void)stream_decoder.memconfig(
						stream_decoder.coder,
						memlimit, &memusage, 0);
			}
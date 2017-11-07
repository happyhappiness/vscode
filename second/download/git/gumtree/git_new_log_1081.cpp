die("%s failed with error code %d: %s",
		    (p->pcre2_jit_on ? "pcre2_jit_match" : "pcre2_match"), ret,
		    errbuf);
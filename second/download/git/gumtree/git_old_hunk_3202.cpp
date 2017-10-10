		}
	} else if (output_eol(crlf_action) == EOL_CRLF) {
		/*
		 * CRLFs would be added by checkout:
		 * check if we have "naked" LFs
		 */
		if (stats->lf != stats->crlf) {
			if (checksafe == SAFE_CRLF_WARN)
				warning("LF will be replaced by CRLF in %s.\nThe file will have its original line endings in your working directory.", path);
			else /* i.e. SAFE_CRLF_FAIL */
				die("LF would be replaced by CRLF in %s", path);
		}
	}

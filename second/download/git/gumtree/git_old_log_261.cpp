fprintf_ln(stderr,
				   Q_("Hunk #%d succeeded at %d (offset %d line).",
				      "Hunk #%d succeeded at %d (offset %d lines).",
				      offset),
				   nth_fragment, applied_pos + 1, offset);
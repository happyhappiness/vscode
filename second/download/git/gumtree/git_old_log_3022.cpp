die(Q_("premature end of pack file, %lu byte missing",
			       "premature end of pack file, %lu bytes missing",
			       len),
			    len);
die(Q_("git diff header lacks filename information when removing "
					       "%d leading pathname component (line %d)",
					       "git diff header lacks filename information when removing "
					       "%d leading pathname components (line %d)",
					       p_value),
					    p_value, linenr);
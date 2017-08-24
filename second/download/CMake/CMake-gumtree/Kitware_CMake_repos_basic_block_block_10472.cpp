(uudecode->state == ST_FIND_HEAD &&
			    (uudecode->total > 0 || total > 0)) {
				uudecode->state = ST_IGNORE;
				used = avail_in;
				goto finish;
			}
die("Path '%s' is in the index, but not '%s'.\n"
			    "Did you mean ':%d:%s' aka ':%d:./%s'?",
			    fullname.buf, filename,
			    ce_stage(ce), fullname.buf,
			    ce_stage(ce), filename);
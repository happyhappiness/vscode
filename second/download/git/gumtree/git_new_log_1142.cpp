ret = error("unable to move logfile logs/%s to logs/"TMP_RENAMED_LOG": %s",
			    oldrefname, strerror(errno));
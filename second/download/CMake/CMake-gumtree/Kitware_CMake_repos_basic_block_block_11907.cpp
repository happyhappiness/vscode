((lha->setflag & UNIX_MODE_IS_SET) == 0 &&
	    (lha->dos_attr & 1) != 0)
		lha->mode &= ~(0222)
			die_errno(_("could not close %s"), path);
		return -1;
	}
	return 0;
}

void sleep_millisec(int millisec)
{
	poll(NULL, 0, millisec);
}

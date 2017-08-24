{
		wintm.QuadPart = WINTIME(birthtime, birthtime_nanos);
		fbtime.dwLowDateTime = wintm.LowPart;
		fbtime.dwHighDateTime = wintm.HighPart;
		pfbtime = &fbtime;
	}
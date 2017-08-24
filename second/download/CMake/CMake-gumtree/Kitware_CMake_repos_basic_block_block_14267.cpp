{
		/* append "UNC\" ---> "\\?\UNC\" */
		wcsncpy(wsp, L"UNC\\", 4);
		wsp += 4;
		slen -= 4;
	}
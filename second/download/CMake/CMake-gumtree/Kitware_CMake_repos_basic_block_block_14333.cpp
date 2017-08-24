(i = 0; i < (int)(sizeof(doserrors)/sizeof(doserrors[0])); i++)
	{
		if (doserrors[i].winerr == e)
		{
			errno = doserrors[i].doserr;
			return;
		}
	}
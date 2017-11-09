const char *gai_strerror(int errcode)
{
#ifdef HAVE_HSTRERROR
	int			hcode;

	switch (errcode)
	{
		case EAI_NONAME:
			hcode = HOST_NOT_FOUND;
			break;
		case EAI_AGAIN:
			hcode = TRY_AGAIN;
			break;
		case EAI_FAIL:
		default:
			hcode = NO_RECOVERY;
			break;
	}

	return hstrerror(hcode);
#else							/* !HAVE_HSTRERROR */

	switch (errcode)
	{
		case EAI_NONAME:
			return "Unknown host";
		case EAI_AGAIN:
			return "Host name lookup failure";
#ifdef EAI_BADFLAGS
		case EAI_BADFLAGS:
			return "Invalid argument";
#endif
#ifdef EAI_FAMILY
		case EAI_FAMILY:
			return "Address family not supported";
#endif
#ifdef EAI_MEMORY
		case EAI_MEMORY:
			return "Not enough memory";
#endif
#ifdef EAI_NODATA
		case EAI_NODATA:
			return "No host data of that type was found";
#endif
#ifdef EAI_SERVICE
		case EAI_SERVICE:
			return "Class type not found";
#endif
#ifdef EAI_SOCKTYPE
		case EAI_SOCKTYPE:
			return "Socket type not supported";
#endif
		default:
			return "Unknown server error";
	}
#endif   /* HAVE_HSTRERROR */
}
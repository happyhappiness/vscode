const char *rcode_str (int rcode)
{
	static char buf[32];
	switch (rcode)
	{
#if (defined (__NAMESER)) && (__NAMESER >= 19991006)
		case ns_r_noerror:  return ("NOERROR");
		case ns_r_formerr:  return ("FORMERR");
		case ns_r_servfail: return ("SERVFAIL");
		case ns_r_nxdomain: return ("NXDOMAIN");
		case ns_r_notimpl:  return ("NOTIMPL");
		case ns_r_refused:  return ("REFUSED");
		case ns_r_yxdomain: return ("YXDOMAIN");
		case ns_r_yxrrset:  return ("YXRRSET");
		case ns_r_nxrrset:  return ("NXRRSET");
		case ns_r_notauth:  return ("NOTAUTH");
		case ns_r_notzone:  return ("NOTZONE");
		case ns_r_max:      return ("MAX");
		case ns_r_badsig:   return ("BADSIG");
		case ns_r_badkey:   return ("BADKEY");
		case ns_r_badtime:  return ("BADTIME");
/* #endif __NAMESER >= 19991006 */
#elif (defined (__BIND)) && (__BIND >= 19950621)
		case NOERROR:	    return ("NOERROR");
		case FORMERR:	    return ("FORMERR");
		case SERVFAIL:	    return ("SERVFAIL");
		case NXDOMAIN:	    return ("NXDOMAIN");
		case NOTIMP:	    return ("NOTIMP");
		case REFUSED:	    return ("REFUSED");
#if defined (YXDOMAIN) && defined (NXRRSET)
		case YXDOMAIN:	    return ("YXDOMAIN");
		case YXRRSET:	    return ("YXRRSET");
		case NXRRSET:	    return ("NXRRSET");
		case NOTAUTH:	    return ("NOTAUTH");
		case NOTZONE:	    return ("NOTZONE");
#endif  /* RFC2136 rcodes */
#endif /* __BIND >= 19950621 */
		default:
			ssnprintf (buf, sizeof (buf), "RCode%i", rcode);
			return (buf);
	}
}
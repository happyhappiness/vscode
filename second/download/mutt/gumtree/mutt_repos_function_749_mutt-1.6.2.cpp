static int getnameinfo_err(int ret)
{
  int err;
  dprint (1, (debugfile, "getnameinfo: "));
  switch(ret)
  {
     case EAI_AGAIN:
       dprint (1, (debugfile, "The name could not be resolved at this time.  Future attempts may succeed.\n"));
       err=SASL_TRYAGAIN;
       break;
     case EAI_BADFLAGS:
       dprint (1, (debugfile, "The flags had an invalid value.\n"));
       err=SASL_BADPARAM;
       break;
     case EAI_FAIL:
       dprint (1, (debugfile, "A non-recoverable error occurred.\n"));
       err=SASL_FAIL;
       break;
     case EAI_FAMILY:
       dprint (1, (debugfile, "The address family was not recognized or the address length was invalid for the specified family.\n"));
       err=SASL_BADPROT;
       break;
     case EAI_MEMORY:
       dprint (1, (debugfile, "There was a memory allocation failure.\n"));
       err=SASL_NOMEM;
       break;
     case EAI_NONAME:
       dprint (1, (debugfile, "The name does not resolve for the supplied parameters.  NI_NAMEREQD is set and the host's name cannot be located, or both nodename and servname were null.\n"));
       err=SASL_FAIL; /* no real equivalent */
       break;
     case EAI_SYSTEM:
       dprint (1, (debugfile, "A system error occurred.  The error code can be found in errno(%d,%s)).\n",errno,strerror(errno)));
       err=SASL_FAIL; /* no real equivalent */
       break;
     default:
       dprint (1, (debugfile, "Unknown error %d\n",ret));
       err=SASL_FAIL; /* no real equivalent */
       break;
  }
  return err;
}
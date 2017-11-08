static int
win32_compute_revents (HANDLE h, int *p_sought)
{
  int i, ret, happened;
  INPUT_RECORD *irbuffer;
  DWORD avail, nbuffer;
  BOOL bRet;
  IO_STATUS_BLOCK iosb;
  FILE_PIPE_LOCAL_INFORMATION fpli;
  static PNtQueryInformationFile NtQueryInformationFile;
  static BOOL once_only;

  switch (GetFileType (h))
    {
    case FILE_TYPE_PIPE:
      if (!once_only)
	{
	  NtQueryInformationFile = (PNtQueryInformationFile)
	    GetProcAddress (GetModuleHandle ("ntdll.dll"),
			    "NtQueryInformationFile");
	  once_only = TRUE;
	}

      happened = 0;
      if (PeekNamedPipe (h, NULL, 0, NULL, &avail, NULL) != 0)
	{
	  if (avail)
	    happened |= *p_sought & (POLLIN | POLLRDNORM);
	}
      else if (GetLastError () == ERROR_BROKEN_PIPE)
	happened |= POLLHUP;

      else
	{
	  /* It was the write-end of the pipe.  Check if it is writable.
	     If NtQueryInformationFile fails, optimistically assume the pipe is
	     writable.  This could happen on Win9x, where NtQueryInformationFile
	     is not available, or if we inherit a pipe that doesn't permit
	     FILE_READ_ATTRIBUTES access on the write end (I think this should
	     not happen since WinXP SP2; WINE seems fine too).  Otherwise,
	     ensure that enough space is available for atomic writes.  */
	  memset (&iosb, 0, sizeof (iosb));
	  memset (&fpli, 0, sizeof (fpli));

	  if (!NtQueryInformationFile
	      || NtQueryInformationFile (h, &iosb, &fpli, sizeof (fpli),
					 FilePipeLocalInformation)
	      || fpli.WriteQuotaAvailable >= PIPE_BUF
	      || (fpli.OutboundQuota < PIPE_BUF &&
		  fpli.WriteQuotaAvailable == fpli.OutboundQuota))
	    happened |= *p_sought & (POLLOUT | POLLWRNORM | POLLWRBAND);
	}
      return happened;

    case FILE_TYPE_CHAR:
      ret = WaitForSingleObject (h, 0);
      if (!IsConsoleHandle (h))
	return ret == WAIT_OBJECT_0 ? *p_sought & ~(POLLPRI | POLLRDBAND) : 0;

      nbuffer = avail = 0;
      bRet = GetNumberOfConsoleInputEvents (h, &nbuffer);
      if (bRet)
	{
	  /* Input buffer.  */
	  *p_sought &= POLLIN | POLLRDNORM;
	  if (nbuffer == 0)
	    return POLLHUP;
	  if (!*p_sought)
	    return 0;

	  irbuffer = (INPUT_RECORD *) alloca (nbuffer * sizeof (INPUT_RECORD));
	  bRet = PeekConsoleInput (h, irbuffer, nbuffer, &avail);
	  if (!bRet || avail == 0)
	    return POLLHUP;

	  for (i = 0; i < avail; i++)
	    if (irbuffer[i].EventType == KEY_EVENT)
	      return *p_sought;
	  return 0;
	}
      else
	{
	  /* Screen buffer.  */
	  *p_sought &= POLLOUT | POLLWRNORM | POLLWRBAND;
	  return *p_sought;
	}

    default:
      ret = WaitForSingleObject (h, 0);
      if (ret == WAIT_OBJECT_0)
	return *p_sought & ~(POLLPRI | POLLRDBAND);

      return *p_sought & (POLLOUT | POLLWRNORM | POLLWRBAND);
    }
}
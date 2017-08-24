{
  FILETIME filetime_a, filetime_m;

  TIME_T_TO_FILETIME(atime, &filetime_a);
  TIME_T_TO_FILETIME(mtime, &filetime_m);

  if (!SetFileTime(handle, NULL, &filetime_a, &filetime_m)) {
    return -1;
  }

  return 0;
}
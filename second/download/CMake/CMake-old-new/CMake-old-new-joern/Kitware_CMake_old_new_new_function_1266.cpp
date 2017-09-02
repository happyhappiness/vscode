bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdString>& files)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  TAR *t;
  char buf[TAR_MAXPATHLEN];
  char pathname[TAR_MAXPATHLEN];

  // Ok, this libtar is not const safe. for now use auto_ptr hack
  char* realName = new char[ strlen(outFileName) + 1 ];
  std::auto_ptr<char> realNamePtr(realName);
  strcpy(realName, outFileName);
  if (tar_open(&t, realName,
      NULL,
      O_WRONLY | O_CREAT, 0644,
      TAR_VERBOSE
      | 0) == -1)
    {
    cmSystemTools::Error("Problem with tar_open(): ", strerror(errno));
    return false;
    }

  std::vector<cmStdString>::const_iterator it;
  for (it = files.begin(); it != files.end(); ++ it )
    {
    strncpy(pathname, it->c_str(), sizeof(pathname));
    pathname[sizeof(pathname)-1] = 0;
    strncpy(buf, pathname, sizeof(buf));
    buf[sizeof(buf)-1] = 0;
    if (tar_append_tree(t, buf, pathname) != 0)
      {
      cmOStringStream ostr;
      ostr << "Problem with tar_append_tree(\"" << buf << "\", \"" << pathname << "\"): "
        << strerror(errno);
      cmSystemTools::Error(ostr.str().c_str());
      tar_close(t);
      return false;
      }
    }

  if (tar_append_eof(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_append_eof(): ", strerror(errno));
    tar_close(t);
    return false;
    }

  if (tar_close(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_close(): ", strerror(errno));
    return false;
    }
  return true;
#else
  return false;
#endif
}
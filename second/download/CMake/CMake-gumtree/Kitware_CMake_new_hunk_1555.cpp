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

bool cmSystemTools::ExtractTar(const char* outFileName, const std::vector<cmStdString>& files)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  TAR *t;
  // Ok, this libtar is not const safe. for now use auto_ptr hack
  char* realName = new char[ strlen(outFileName) + 1 ];
  std::auto_ptr<char> realNamePtr(realName);
  strcpy(realName, outFileName);
  if (tar_open(&t, realName,
      NULL,
      O_RDONLY
#ifdef _WIN32
      | O_BINARY
#endif
      , 0,
      TAR_VERBOSE
      | 0) == -1)
    {
    cmSystemTools::Error("Problem with tar_open(): ", strerror(errno));
    return false;
    }

  if (tar_extract_all(t, 0) != 0)
  {
    cmSystemTools::Error("Problem with tar_extract_all(): ", strerror(errno));
    return false;
  }

  if (tar_close(t) != 0)
    {
    cmSystemTools::Error("Problem with tar_close(): ", strerror(errno));
    return false;
    }
  return true;
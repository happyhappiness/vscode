void SystemTools::ClassInitialize()
{
  // Allocate the translation map first.
  SystemTools::TranslationMap = new SystemToolsTranslationMap;

  // Add some special translation paths for unix.  These are not added
  // for windows because drive letters need to be maintained.  Also,
  // there are not sym-links and mount points on windows anyway.
#if !defined(_WIN32) || defined(__CYGWIN__)
  // Work-around an SGI problem by always adding this mapping:
  SystemTools::AddTranslationPath("/tmp_mnt/", "/");
  // The tmp path is frequently a logical path so always keep it:
  SystemTools::AddKeepPath("/tmp/");

  // If the current working directory is a logical path then keep the
  // logical name.
  if(const char* pwd = getenv("PWD"))
    {
    char buf[2048];
    if(const char* cwd = Getcwd(buf, 2048))
      {
      kwsys_stl::string pwd_path;
      Realpath(pwd, pwd_path);
      if(cwd == pwd_path && strcmp(cwd, pwd) != 0)
        {
#if defined(__HP_aCC)
        fprintf(stderr, "cwd=[%s]\npwd=[%s]\npwd_path=[%s]\n",
                cwd, pwd, pwd_path.c_str());
#endif
        // The current working directory is a logical path.  Split
        // both the logical and physical paths into their components.
        kwsys_stl::vector<kwsys_stl::string> cwd_components;
        kwsys_stl::vector<kwsys_stl::string> pwd_components;
        SystemTools::SplitPath(cwd, cwd_components);
        SystemTools::SplitPath(pwd, pwd_components);

        // Remove the common ending of the paths to leave only the
        // part that changes under the logical mapping.
        kwsys_stl::vector<kwsys_stl::string>::iterator ic = cwd_components.end();
        kwsys_stl::vector<kwsys_stl::string>::iterator ip = pwd_components.end();
        for(;ip != pwd_components.begin() && ic != cwd_components.begin() &&
              *(ip-1) == *(ic-1); --ip,--ic);
        cwd_components.erase(ic, cwd_components.end());
        pwd_components.erase(ip, pwd_components.end());

        // Reconstruct the string versions of the part of the path
        // that changed.
        kwsys_stl::string cwd_changed = SystemTools::JoinPath(cwd_components);
        kwsys_stl::string pwd_changed = SystemTools::JoinPath(pwd_components);

        // Add the translation to keep the logical path name.
        if(!cwd_changed.empty() && !pwd_changed.empty())
          {
#if defined(__HP_aCC)
          fprintf(stderr, "adding [%s]->[%s]\n", cwd_changed.c_str(),
                  pwd_changed.c_str());
#endif
          SystemTools::AddTranslationPath(cwd_changed.c_str(),
                                          pwd_changed.c_str());
          }
        }
      }
    }
#endif
}
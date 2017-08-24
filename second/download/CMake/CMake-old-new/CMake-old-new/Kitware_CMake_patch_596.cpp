@@ -2280,10 +2280,6 @@ void SystemTools::ClassInitialize()
       Realpath(pwd, pwd_path);
       if(cwd == pwd_path && strcmp(cwd, pwd) != 0)
         {
-#if defined(__HP_aCC)
-        fprintf(stderr, "cwd=[%s]\npwd=[%s]\npwd_path=[%s]\n",
-                cwd, pwd, pwd_path.c_str());
-#endif
         // The current working directory is a logical path.  Split
         // both the logical and physical paths into their components.
         kwsys_stl::vector<kwsys_stl::string> cwd_components;
@@ -2308,10 +2304,6 @@ void SystemTools::ClassInitialize()
         // Add the translation to keep the logical path name.
         if(!cwd_changed.empty() && !pwd_changed.empty())
           {
-#if defined(__HP_aCC)
-          fprintf(stderr, "adding [%s]->[%s]\n", cwd_changed.c_str(),
-                  pwd_changed.c_str());
-#endif
           SystemTools::AddTranslationPath(cwd_changed.c_str(),
                                           pwd_changed.c_str());
           }
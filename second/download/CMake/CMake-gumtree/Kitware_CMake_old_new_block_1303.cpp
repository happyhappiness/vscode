{
#if defined(__HP_aCC)
          fprintf(stderr, "adding [%s]->[%s]\n", cwd_changed.c_str(),
                  pwd_changed.c_str());
#endif
          SystemTools::AddTranslationPath(cwd_changed.c_str(),
                                          pwd_changed.c_str());
          }
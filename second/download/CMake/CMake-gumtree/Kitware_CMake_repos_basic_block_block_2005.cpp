{
#if defined(_WIN32)
      const std::string s = Encoding::ToNarrow(*i);
      kwsysUnPutEnv(s.c_str());
#else
      kwsysUnPutEnv(*i);
#endif
      free(const_cast<envchar*>(*i));
    }
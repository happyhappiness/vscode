{
#ifdef _WIN32
    wchar_t* wname = cmsysEncoding_DupToWide(name);
    lexer->file = _wfopen(wname, L"rb");
    free(wname);
#else
    lexer->file = fopen(name, "rb");
#endif
    if (lexer->file) {
      if (bom) {
        *bom = cmListFileLexer_ReadBOM(lexer->file);
      }
    } else {
      result = 0;
    }
  }
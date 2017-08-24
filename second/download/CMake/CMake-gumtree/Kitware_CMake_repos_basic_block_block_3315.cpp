(aa = argList; aa != NULL; aa = aa->link) {
      if (ISFLAG("--")) { decode = False; continue; }
      if (aa->name[0] == '-' && decode) continue;
      numFileNames++;
      if (longestFileName < (Int32)strlen(aa->name) )
         longestFileName = (Int32)strlen(aa->name);
   }
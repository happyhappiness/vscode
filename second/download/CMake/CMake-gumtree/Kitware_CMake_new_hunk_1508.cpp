  fprintf(fout,"{NULL, NULL, 0, NULL}};\n\n");

  

#ifdef _WIN32

  fprintf(fout,"extern  \"C\" {__declspec( dllexport) void init%s();}\n\n",

          kitName);

  fprintf(fout,"void init%s()\n{\n",kitName);

#else

  fprintf(fout,"extern  \"C\" {void initlib%s();}\n\n",kitName);

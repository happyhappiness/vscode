{
   HINSTANCE hLib;

   if(BZ2DLLLoaded==1){return 0;}
   hLib=LoadLibrary(BZ2_LIBNAME);
   if(hLib == NULL){
      fprintf(stderr,"Can't load %s\n",BZ2_LIBNAME);
      return -1;
   }
   BZ2_bzlibVersion=GetProcAddress(hLib,"BZ2_bzlibVersion");
   BZ2_bzopen=GetProcAddress(hLib,"BZ2_bzopen");
   BZ2_bzdopen=GetProcAddress(hLib,"BZ2_bzdopen");
   BZ2_bzread=GetProcAddress(hLib,"BZ2_bzread");
   BZ2_bzwrite=GetProcAddress(hLib,"BZ2_bzwrite");
   BZ2_bzflush=GetProcAddress(hLib,"BZ2_bzflush");
   BZ2_bzclose=GetProcAddress(hLib,"BZ2_bzclose");
   BZ2_bzerror=GetProcAddress(hLib,"BZ2_bzerror");

   if (!BZ2_bzlibVersion || !BZ2_bzopen || !BZ2_bzdopen
       || !BZ2_bzread || !BZ2_bzwrite || !BZ2_bzflush
       || !BZ2_bzclose || !BZ2_bzerror) {
      fprintf(stderr,"GetProcAddress failed.\n");
      return -1;
   }
   BZ2DLLLoaded=1;
   BZ2DLLhLib=hLib;
   return 0;

}
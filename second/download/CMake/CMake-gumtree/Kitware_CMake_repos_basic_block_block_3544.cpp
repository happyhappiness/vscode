{
   if(BZ2DLLLoaded==0){return 0;}
   FreeLibrary(BZ2DLLhLib);
   BZ2DLLLoaded=0;
}
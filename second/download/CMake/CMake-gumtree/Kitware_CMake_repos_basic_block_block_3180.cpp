{
   IntNative      i;
   struct MY_STAT statBuf;

   i = MY_LSTAT ( name, &statBuf );
   if (i != 0) return True;
   if (MY_S_ISREG(statBuf.st_mode)) return False;
   return True;
}
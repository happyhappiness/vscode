wchar_t 
btowc (int c)
{
   wchar_t wtmp[2];
   char tmp[2];

   tmp[0] = c;
   tmp[1] = 0;

   mbtowc (wtmp, tmp, 1);
   return wtmp[0];
}
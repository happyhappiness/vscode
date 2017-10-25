static void printoption(struct UrlData *data,
			const char *direction, int cmd, int option)
{
   char *fmt;
   char *opt;
   
   if (data->bits.verbose)
   {
      if (cmd == IAC)
      {
         if (TELCMD_OK(option))
            printf("%s IAC %s\n", direction, TELCMD(option));
         else
            printf("%s IAC %d\n", direction, option);
      }
      else
      {
         fmt = (cmd == WILL) ? "WILL" : (cmd == WONT) ? "WONT" :
            (cmd == DO) ? "DO" : (cmd == DONT) ? "DONT" : 0;
         if (fmt)
         {
            if (TELOPT_OK(option))
               opt = TELOPT(option);
            else if (option == TELOPT_EXOPL)
               opt = "EXOPL";
            else
               opt = NULL;

            if(opt)
               printf("%s %s %s\n", direction, fmt, opt);
            else
               printf("%s %s %d\n", direction, fmt, option);
         }
         else
            printf("%s %d %d\n", direction, cmd, option);
      }
   }
}
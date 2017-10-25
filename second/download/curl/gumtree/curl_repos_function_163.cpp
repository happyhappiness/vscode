static void printsub(struct UrlData *data,
		     int direction,		/* '<' or '>' */
		     unsigned char *pointer,	/* where suboption data is */
		     int length)		/* length of suboption data */

{
   int i = 0;

   if (data->bits.verbose)
   {
      if (direction)
      {
         printf("%s IAC SB ", (direction == '<')? "RCVD":"SENT");
         if (length >= 3)
         {
            int j;

            i = pointer[length-2];
            j = pointer[length-1];

            if (i != IAC || j != SE)
            {
               printf("(terminated by ");
               if (TELOPT_OK(i))
                  printf("%s ", TELOPT(i));
               else if (TELCMD_OK(i))
                  printf("%s ", TELCMD(i));
               else
                  printf("%d ", i);
               if (TELOPT_OK(j))
                  printf("%s", TELOPT(j));
               else if (TELCMD_OK(j))
                  printf("%s", TELCMD(j));
               else
                  printf("%d", j);
               printf(", not IAC SE!) ");
            }
         }
         length -= 2;
      }
      if (length < 1)
      {
         printf("(Empty suboption?)");
         return;
      }

      if (TELOPT_OK(pointer[0]))
	 printf("%s (unknown)", TELOPT(pointer[0]));
      else
	 printf("%d (unknown)", pointer[i]);
      for (i = 1; i < length; i++)
	 printf(" %d", pointer[i]);
      
      if (direction)
      {
         printf("\n");
      }
   }
}
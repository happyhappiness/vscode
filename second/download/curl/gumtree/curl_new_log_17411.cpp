puts(" -c/--cookie-jar <file> Write all cookies to this file after operation (H)\n"
       " -C/--continue-at <offset> Specify absolute resume offset\n"
       " -d/--data <data>   HTTP POST data (H)\n"
       "    --data-ascii <data>   HTTP POST ASCII data (H)\n"
       "    --data-binary <data>  HTTP POST binary data (H)\n"
       "    --disable-epsv  Prevents curl from using EPSV (F)\n"
       " -D/--dump-header <file> Write the headers to this file\n"
       "    --egd-file <file> EGD socket path for random data (SSL)\n"
#ifdef USE_ENVIRONMENT
       "    --environment   Write result codes to environment variables (RISC OS)\n"
#endif
       " -e/--referer       Referer page (H)");
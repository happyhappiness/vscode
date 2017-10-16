       " -z/--time-cond <time> Includes a time condition to the server (H)\n"
       " -Z/--max-redirs <num> Set maximum number of redirections allowed (H)\n"
       " -0/--http1.0       Force usage of HTTP 1.0 (H)\n"
       " -1/--tlsv1         Force usage of TLSv1 (H)\n"
       " -2/--sslv2         Force usage of SSLv2 (H)\n"
       " -3/--sslv3         Force usage of SSLv3 (H)");
  puts(" -#/--progress-bar  Display transfer progress as a progress bar");
}

struct LongShort {
  const char *letter;
  const char *lname;
  bool extraparam;

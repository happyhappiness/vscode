       " -3/--sslv3         Force usage of SSLv3 (H)");
  puts(" -#/--progress-bar  Display transfer progress as a progress bar\n"
       "    --crlf          Convert LF to CRLF in upload. Useful for MVS (OS/390)");
}

struct LongShort {
  char *letter;
  char *lname;
  bool extraparam;
};

struct Configurable {
  char *random_file;
  char *egd_file;
  char *useragent;
  char *cookie;
  bool use_resume;
  int resume_from;
  char *postfields;
  long postfieldsize;
  char *referer;
  long timeout;
  long connecttimeout;

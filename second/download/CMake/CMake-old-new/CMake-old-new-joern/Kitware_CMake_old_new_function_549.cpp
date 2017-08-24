void DoHeaderLine()
    {
    // Look for header fields that we need.
    if(strncmp(this->Line.c_str(), "commit ", 7) == 0)
      {
      this->Rev.Rev = this->Line.c_str()+7;
      }
    else if(strncmp(this->Line.c_str(), "author ", 7) == 0)
      {
      Person author;
      this->ParsePerson(this->Line.c_str()+7, author);
      this->Rev.Author = author.Name;
      this->Rev.EMail = author.EMail;

      // Convert the time to a human-readable format that is also easy
      // to machine-parse: "CCYY-MM-DD hh:mm:ss".
      time_t seconds = static_cast<time_t>(author.Time);
      struct tm* t = gmtime(&seconds);
      char dt[1024];
      sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d",
              t->tm_year+1900, t->tm_mon+1, t->tm_mday,
              t->tm_hour, t->tm_min, t->tm_sec);
      this->Rev.Date = dt;

      // Add the time-zone field "+zone" or "-zone".
      char tz[32];
      if(author.TimeZone >= 0)
        {
        sprintf(tz, " +%04ld", author.TimeZone);
        }
      else
        {
        sprintf(tz, " -%04ld", -author.TimeZone);
        }
      this->Rev.Date += tz;
      }
    }
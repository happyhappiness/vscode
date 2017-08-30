      }
    this->Rev.Log += "\n";
    }

  std::string FormatDateTime(Person const& person)
    {
    // Convert the time to a human-readable format that is also easy
    // to machine-parse: "CCYY-MM-DD hh:mm:ss".
    time_t seconds = static_cast<time_t>(person.Time);
    struct tm* t = gmtime(&seconds);
    char dt[1024];
    sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year+1900, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    std::string out = dt;

    // Add the time-zone field "+zone" or "-zone".
    char tz[32];
    if(person.TimeZone >= 0)
      {
      sprintf(tz, " +%04ld", person.TimeZone);
      }
    else
      {
      sprintf(tz, " -%04ld", -person.TimeZone);
      }
    out += tz;
    return out;
    }
};

char const cmCTestGIT::CommitParser::SectionSep[SectionCount] =
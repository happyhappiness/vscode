@@ -503,57 +503,15 @@ class cmCTestGIT::CommitParser: public cmCTestGIT::DiffParser
       this->ParsePerson(this->Line.c_str()+7, author);
       this->Rev.Author = author.Name;
       this->Rev.EMail = author.EMail;
-
-      // Convert the time to a human-readable format that is also easy
-      // to machine-parse: "CCYY-MM-DD hh:mm:ss".
-      time_t seconds = static_cast<time_t>(author.Time);
-      struct tm* t = gmtime(&seconds);
-      char dt[1024];
-      sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d",
-              t->tm_year+1900, t->tm_mon+1, t->tm_mday,
-              t->tm_hour, t->tm_min, t->tm_sec);
-      this->Rev.Date = dt;
-
-      // Add the time-zone field "+zone" or "-zone".
-      char tz[32];
-      if(author.TimeZone >= 0)
-        {
-        sprintf(tz, " +%04ld", author.TimeZone);
-        }
-      else
-        {
-        sprintf(tz, " -%04ld", -author.TimeZone);
-        }
-      this->Rev.Date += tz;
+      this->Rev.Date = this->FormatDateTime(author);
       }
     else if(strncmp(this->Line.c_str(), "committer ", 10) == 0)
       {
       Person committer;
       this->ParsePerson(this->Line.c_str()+10, committer);
       this->Rev.Committer = committer.Name;
       this->Rev.CommitterEMail = committer.EMail;
-
-      // Convert the time to a human-readable format that is also easy
-      // to machine-parse: "CCYY-MM-DD hh:mm:ss".
-      time_t seconds = static_cast<time_t>(committer.Time);
-      struct tm* t = gmtime(&seconds);
-      char dt[1024];
-      sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d",
-              t->tm_year+1900, t->tm_mon+1, t->tm_mday,
-              t->tm_hour, t->tm_min, t->tm_sec);
-      this->Rev.CommitDate = dt;
-
-      // Add the time-zone field "+zone" or "-zone".
-      char tz[32];
-      if(committer.TimeZone >= 0)
-        {
-        sprintf(tz, " +%04ld", committer.TimeZone);
-        }
-      else
-        {
-        sprintf(tz, " -%04ld", -committer.TimeZone);
-        }
-      this->Rev.CommitDate += tz;
+      this->Rev.CommitDate = this->FormatDateTime(committer);
       }
     }
 
@@ -566,6 +524,32 @@ class cmCTestGIT::CommitParser: public cmCTestGIT::DiffParser
       }
     this->Rev.Log += "\n";
     }
+
+  std::string FormatDateTime(Person const& person)
+    {
+    // Convert the time to a human-readable format that is also easy
+    // to machine-parse: "CCYY-MM-DD hh:mm:ss".
+    time_t seconds = static_cast<time_t>(person.Time);
+    struct tm* t = gmtime(&seconds);
+    char dt[1024];
+    sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d",
+            t->tm_year+1900, t->tm_mon+1, t->tm_mday,
+            t->tm_hour, t->tm_min, t->tm_sec);
+    std::string out = dt;
+
+    // Add the time-zone field "+zone" or "-zone".
+    char tz[32];
+    if(person.TimeZone >= 0)
+      {
+      sprintf(tz, " +%04ld", person.TimeZone);
+      }
+    else
+      {
+      sprintf(tz, " -%04ld", -person.TimeZone);
+      }
+    out += tz;
+    return out;
+    }
 };
 
 char const cmCTestGIT::CommitParser::SectionSep[SectionCount] =
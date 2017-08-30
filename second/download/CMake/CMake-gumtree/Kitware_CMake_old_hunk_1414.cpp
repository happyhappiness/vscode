  const char *terse;

  const char *full;

  char tmp[1024];

  sprintf(tmp,"Version %d.%d (%s)", cmake::GetMajorVersion(),

          cmake::GetMinorVersion(), cmVersion::GetReleaseVersion().c_str());

  f << "<html>\n";

  f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";

  f << "<ul>\n";


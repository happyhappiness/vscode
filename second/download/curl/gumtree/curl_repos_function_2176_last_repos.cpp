static void printoption(struct Curl_easy *data,
                        const char *direction, int cmd, int option)
{
  const char *fmt;
  const char *opt;

  if(data->set.verbose) {
    if(cmd == CURL_IAC) {
      if(CURL_TELCMD_OK(option))
        infof(data, "%s IAC %s\n", direction, CURL_TELCMD(option));
      else
        infof(data, "%s IAC %d\n", direction, option);
    }
    else {
      fmt = (cmd == CURL_WILL) ? "WILL" : (cmd == CURL_WONT) ? "WONT" :
        (cmd == CURL_DO) ? "DO" : (cmd == CURL_DONT) ? "DONT" : 0;
      if(fmt) {
        if(CURL_TELOPT_OK(option))
          opt = CURL_TELOPT(option);
        else if(option == CURL_TELOPT_EXOPL)
          opt = "EXOPL";
        else
          opt = NULL;

        if(opt)
          infof(data, "%s %s %s\n", direction, fmt, opt);
        else
          infof(data, "%s %s %d\n", direction, fmt, option);
      }
      else
        infof(data, "%s %d %d\n", direction, cmd, option);
    }
  }
}
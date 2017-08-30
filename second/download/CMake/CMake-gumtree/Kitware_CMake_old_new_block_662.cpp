int cmcmd::ExecuteEchoColor(std::vector<std::string>& args)
{
  // The arguments are
  //   argv[0] == <cmake-executable>
  //   argv[1] == cmake_echo_color

  bool enabled = true;
  int color = cmsysTerminal_Color_Normal;
  bool newline = true;
  for(unsigned int i=2; i < args.size(); ++i)
    {
    if(args[i].find("--switch=") == 0)
      {
      // Enable or disable color based on the switch value.
      std::string value = args[i].substr(9);
      if(!value.empty())
        {
        if(cmSystemTools::IsOn(value.c_str()))
          {
          enabled = true;
          }
        else
          {
          enabled = false;
          }
        }
      }
    else if(args[i] == "--normal")
      {
      color = cmsysTerminal_Color_Normal;
      }
    else if(args[i] == "--black")
      {
      color = cmsysTerminal_Color_ForegroundBlack;
      }
    else if(args[i] == "--red")
      {
      color = cmsysTerminal_Color_ForegroundRed;
      }
    else if(args[i] == "--green")
      {
      color = cmsysTerminal_Color_ForegroundGreen;
      }
    else if(args[i] == "--yellow")
      {
      color = cmsysTerminal_Color_ForegroundYellow;
      }
    else if(args[i] == "--blue")
      {
      color = cmsysTerminal_Color_ForegroundBlue;
      }
    else if(args[i] == "--magenta")
      {
      color = cmsysTerminal_Color_ForegroundMagenta;
      }
    else if(args[i] == "--cyan")
      {
      color = cmsysTerminal_Color_ForegroundCyan;
      }
    else if(args[i] == "--white")
      {
      color = cmsysTerminal_Color_ForegroundWhite;
      }
    else if(args[i] == "--bold")
      {
      color |= cmsysTerminal_Color_ForegroundBold;
      }
    else if(args[i] == "--no-newline")
      {
      newline = false;
      }
    else if(args[i] == "--newline")
      {
      newline = true;
      }
    else
      {
      // Color is enabled.  Print with the current color.
      cmSystemTools::MakefileColorEcho(color, args[i].c_str(),
                                       newline, enabled);
      }
    }

  return 0;
}
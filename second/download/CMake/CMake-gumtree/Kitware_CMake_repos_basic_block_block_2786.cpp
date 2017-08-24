{
      std::string output;
      getline(f, output);
      if (!gotTr2xi18n) {
        gotTr2xi18n = output.find("tr2xi18n") != std::string::npos;
      }
      if (output.find("tr2i18n") != std::string::npos) {
        std::cout << "ui_mywidget,h uses tr2i18n, though it should not."
                  << std::endl;
        return -1;
      }
    }
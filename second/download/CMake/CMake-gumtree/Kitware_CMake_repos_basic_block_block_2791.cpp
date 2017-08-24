{
      std::string output;
      getline(f, output);
      if (!gotTr2i18n) {
        gotTr2i18n = output.find("tr2i18n") != std::string::npos;
      }
      if (output.find("tr2xi18n") != std::string::npos) {
        std::cout << "ui_libwidget,h uses tr2xi18n, though it should not."
                  << std::endl;
        return -1;
      }
    }
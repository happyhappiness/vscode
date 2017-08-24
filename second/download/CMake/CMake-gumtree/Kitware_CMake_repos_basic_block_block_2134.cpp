(SystemTools::GetEnv("HOME", homeEnv)) {
        path.replace(0, 1, homeEnv);
      }
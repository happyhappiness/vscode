r(i = 0; i < (int)sizeof(level_names)/(int)sizeof(level_names[0]); i++)
    if(checkprefix(name, level_names[i].name))
      return level_names[i].level;
    int ni = 0;

    sprintf(buffer, "%04d", ni);

    ret = str1 + str2 + buffer;

    while(m_ShortMakeVariableMap.count(ret) && ni < 1000)

      {

      ++ni;

      sprintf(buffer, "%04d", ni);


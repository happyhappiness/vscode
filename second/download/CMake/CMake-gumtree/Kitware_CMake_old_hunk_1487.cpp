  // if there is no restriction on the length of make variables

  // and there are no "." charactors in the string, then return the

  // unmodified combination.

  if((!m_MakefileVariableSize && unmodified.find('.') == s.npos)

     && (!m_MakefileVariableSize && unmodified.find('-') == s.npos))

    {

    return unmodified;

    }



  // see if the variable has been defined before and return

  // the modified version of the variable

  std::map<cmStdString, cmStdString>::iterator i = m_MakeVariableMap.find(unmodified);

  if(i != m_MakeVariableMap.end())

    {

    return i->second;

    }

  // start with the unmodified variable

  std::string ret = unmodified;

  // if this there is no value for m_MakefileVariableSize then

  // the string must have bad characters in it

  if(!m_MakefileVariableSize)

    {

    cmSystemTools::ReplaceString(ret, ".", "_");

    cmSystemTools::ReplaceString(ret, "-", "__");

    int ni = 0;

    char buffer[5];

    // make sure the _ version is not already used, if

    // it is used then add number to the end of the variable

    while(m_ShortMakeVariableMap.count(ret) && ni < 1000)

      {

      ++ni;

      sprintf(buffer, "%04d", ni);

      ret = unmodified + buffer;

      }

    m_ShortMakeVariableMap[ret] = "1";

    m_MakeVariableMap[unmodified] = ret;

    return ret;

    }



  // if the string is greater the 32 chars it is an invalid vairable name

  // for borland make

  if(static_cast<int>(ret.size()) > m_MakefileVariableSize)

    {

    int keep = m_MakefileVariableSize - 8;

    int size = keep + 3;

    std::string str1 = s;

    std::string str2 = s2;


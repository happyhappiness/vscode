  sprintf(num,"%d",static_cast<int>(m_LocalGenerators.size()));

  this->GetCMakeInstance()->AddCacheEntry

    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,

     "number of local generators",

                                          cmCacheManager::INTERNAL);

  

  std::set<cmStdString> notFoundMap;

  // after it is all done do a ConfigureFinalPass


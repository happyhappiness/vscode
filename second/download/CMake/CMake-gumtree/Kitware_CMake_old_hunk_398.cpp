  sprintf(num, "%d", static_cast<int>(this->Makefiles.size()));

  this->GetCMakeInstance()->AddCacheEntry("CMAKE_NUMBER_OF_MAKEFILES", num,

                                          "number of local generators",

                                          cmState::INTERNAL);



  // check for link libraries and include directories containing "NOTFOUND"

  // and for infinite loops


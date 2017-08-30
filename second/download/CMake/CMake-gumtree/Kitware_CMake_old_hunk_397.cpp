  this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", temp,

                      "Minor version of cmake used to create the "

                      "current loaded cache",

                      cmState::INTERNAL);

  sprintf(temp, "%d", cmVersion::GetMajorVersion());

  this->AddCacheEntry("CMAKE_CACHE_MAJOR_VERSION", temp,

                      "Major version of cmake used to create the "

                      "current loaded cache",

                      cmState::INTERNAL);

  sprintf(temp, "%d", cmVersion::GetPatchVersion());

  this->AddCacheEntry("CMAKE_CACHE_PATCH_VERSION", temp,

                      "Patch version of cmake used to create the "

                      "current loaded cache",

                      cmState::INTERNAL);



  // Let us store the current working directory so that if somebody

  // Copies it, he will not be surprised


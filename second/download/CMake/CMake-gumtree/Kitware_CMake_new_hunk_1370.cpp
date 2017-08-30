  sprintf(temp, "%d", cmVersion::GetPatchVersion());

  this->AddDefinition("CMAKE_PATCH_VERSION", temp);



  this->AddDefinition("CMAKE_FILES_DIRECTORY",

                      cmake::GetCMakeFilesDirectory());

}




}



//----------------------------------------------------------------------------

std::string&

cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)

{

  // Look for an existing mapped name for this object file.

  std::map<cmStdString,cmStdString>::iterator it =

    this->UniqueObjectNamesMap.find(sin);



  // If no entry exists create one.

  if(it == this->UniqueObjectNamesMap.end())

    {

    // Start with the original name.

    std::string ssin = sin;



    // Avoid full paths by removing leading slashes.

    std::string::size_type pos = 0;

    for(;pos < ssin.size() && ssin[pos] == '/'; ++pos);

    ssin = ssin.substr(pos);



    // Avoid full paths by removing colons.

    cmSystemTools::ReplaceString(ssin, ":", "_");



    // Avoid relative paths that go up the tree.

    cmSystemTools::ReplaceString(ssin, "../", "__/");



    // Avoid spaces.

    cmSystemTools::ReplaceString(ssin, " ", "_");



    // Mangle the name if necessary.

    if(this->Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES"))

      {

      bool done;

      int cc = 0;

      char rpstr[100];

      sprintf(rpstr, "_p_");

      cmSystemTools::ReplaceString(ssin, "+", rpstr);

      std::string sssin = sin;

      do

        {

        done = true;

        for ( it = this->UniqueObjectNamesMap.begin();

              it != this->UniqueObjectNamesMap.end();

              ++ it )

          {

          if ( it->second == ssin )

            {

            done = false;

            }

          }

        if ( done )

          {

          break;

          }

        sssin = ssin;

        cmSystemTools::ReplaceString(ssin, "_p_", rpstr);

        sprintf(rpstr, "_p%d_", cc++);

        }

      while ( !done );

      }



    // Insert the newly mapped object file name.

    std::map<cmStdString, cmStdString>::value_type e(sin, ssin);

    it = this->UniqueObjectNamesMap.insert(e).first;

    }



  // Return the map entry.

  return it->second;

}



//----------------------------------------------------------------------------

std::string

cmLocalUnixMakefileGenerator3

::CreateMakeVariable(const char* sin, const char* s2in)


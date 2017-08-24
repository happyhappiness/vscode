      {
      printf("Checking -%s-\n", absFilename.c_str());
      }

    const std::string contentsString = this->ReadAll(absFilename);
    if (contentsString.empty())
      {
      std::cerr << "automoc4: empty source file: " << absFilename << std::endl;
      continue;
      }
    const std::string absPath = cmsys::SystemTools::GetFilenamePath(
                cmsys::SystemTools::GetRealPath(absFilename.c_str())) + '/';

    int matchOffset = 0;
    if (!mocIncludeRegExp.find(contentsString.c_str()))
      {
      // no moc #include, look whether we need to create a moc from
      // the .h nevertheless
      const std::string basename =
            cmsys::SystemTools::GetFilenameWithoutLastExtension(absFilename);
      for(std::list<std::string>::const_iterator ext =
                                                    headerExtensions.begin();
          ext != headerExtensions.end();
          ++ext)
        {
        const std::string headername = absPath + basename + (*ext);
        if (cmsys::SystemTools::FileExists(headername.c_str())
                && includedMocs.find(headername) == includedMocs.end()
                && notIncludedMocs.find(headername) == notIncludedMocs.end())
          {
          const std::string currentMoc = "moc_" + basename + ".cpp";
          const std::string contents = this->ReadAll(headername);
          if (qObjectRegExp.find(contents))
            {
            //std::cout << "header contains Q_OBJECT macro";
            notIncludedMocs[headername] = currentMoc;
            }
          break;
          }
        }
      for(std::list<std::string>::const_iterator ext =
                                                    headerExtensions.begin();
          ext != headerExtensions.end();
          ++ext)
        {
        const std::string privateHeaderName = absPath+basename+"_p"+(*ext);
        if (cmsys::SystemTools::FileExists(privateHeaderName.c_str())
           && includedMocs.find(privateHeaderName) == includedMocs.end()
           && notIncludedMocs.find(privateHeaderName) == notIncludedMocs.end())
          {
          const std::string currentMoc = "moc_" + basename + "_p.cpp";
          const std::string contents = this->ReadAll(privateHeaderName);
          if (qObjectRegExp.find(contents))
            {
            //std::cout << "header contains Q_OBJECT macro";
            notIncludedMocs[privateHeaderName] = currentMoc;
            }
          break;
          }
        }
      }
    else
      {
      // for every moc include in the file
      do
        {
        const std::string currentMoc = mocIncludeRegExp.match(1);
        //std::cout << "found moc include: " << currentMoc << std::endl;

        std::string basename = cmsys::SystemTools::
                                  GetFilenameWithoutLastExtension(currentMoc);
        const bool moc_style = this->StartsWith(basename, "moc_");

        // If the moc include is of the moc_foo.cpp style we expect
        // the Q_OBJECT class declaration in a header file.
        // If the moc include is of the foo.moc style we need to look for
        // a Q_OBJECT macro in the current source file, if it contains the
        // macro we generate the moc file from the source file, else from the
        // header.
        // Q_OBJECT
        if (moc_style || !qObjectRegExp.find(contentsString))
          {
          if (moc_style)
            {
            // basename should be the part of the moc filename used for
            // finding the correct header, so we need to remove the moc_ part
            basename = basename.substr(4);
            }

          bool headerFound = false;
          for(std::list<std::string>::const_iterator ext =
                                                    headerExtensions.begin();
              ext != headerExtensions.end();
              ++ext)
            {
            const std::string &sourceFilePath = absPath + basename + (*ext);
            if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
              {
              headerFound = true;
              includedMocs[sourceFilePath] = currentMoc;
              notIncludedMocs.erase(sourceFilePath);
              break;
              }
            }
          if (!headerFound)
            {
            // the moc file is in a subdir => look for the header in the
            // same subdir
            if (currentMoc.find_first_of('/') != std::string::npos)
              {
              const std::string &filepath = absPath
                      + cmsys::SystemTools::GetFilenamePath(currentMoc)
                      + '/' + basename;

              for(std::list<std::string>::const_iterator ext =
                                                    headerExtensions.begin();
                  ext != headerExtensions.end();
                  ++ext)
                {
                const std::string &sourceFilePath = filepath + (*ext);
                if (cmsys::SystemTools::FileExists(sourceFilePath.c_str()))
                  {
                  headerFound = true;
                  includedMocs[sourceFilePath] = currentMoc;
                  notIncludedMocs.erase(sourceFilePath);
                  break;
                  }
                }
              if (!headerFound)
                {
                std::cerr << "automoc4: The file \"" << absFilename
                          << "\" includes the moc file \"" << currentMoc
                          << "\", but neither \"" << absPath << basename
                          << '{' << this->Join(headerExtensions, ',')
                          << "}\" nor \"" << filepath << '{'
                          << this->Join(headerExtensions, ',') << '}'
                          << "\" exist." << std::endl;
                ::exit(EXIT_FAILURE);
                }
              }
            else
              {
              std::cerr << "automoc4: The file \"" << absFilename
                        << "\" includes the moc file \"" << currentMoc
                        << "\", but \"" << absPath << basename << '{'
                        << this->Join(headerExtensions, ',') << '}'
                        << "\" does not exist." << std::endl;
              ::exit(EXIT_FAILURE);
              }
            }
          }
        else
          {
          includedMocs[absFilename] = currentMoc;
          notIncludedMocs.erase(absFilename);
          }
        matchOffset += mocIncludeRegExp.end();
        } while(mocIncludeRegExp.find(contentsString.c_str() + matchOffset));
      }
    }

  std::vector<std::string> headerFiles;

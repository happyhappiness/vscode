      {

      const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());

      cmTarget::LinkLibraries::const_iterator llit;

      if ( ll->size() > 0 )

        {

        targetDeps[tit->first.c_str()] = 1;

        }

      for ( llit = ll->begin(); llit != ll->end(); ++ llit )

        {

        const char* libName = llit->first.c_str();

        std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);

        if ( tarIt == targetNamesNodes.end() )

          {

          sprintf(tgtName, "node%d", cnt++);

          targetDeps[libName] = 2;

          targetNamesNodes[libName] = tgtName;

          //str << "    \"" << tgtName << "\" [ label=\"" << libName <<  "\" shape=\"ellipse\"];" << std::endl;


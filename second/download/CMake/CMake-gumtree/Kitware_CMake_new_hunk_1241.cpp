      {
      const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());
      cmTarget::LinkLibraries::const_iterator llit;
      const char* realTargetName = tit->first.c_str();
      if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
        {
        // Skip ignored targets
        continue;
        }
      if ( ll->size() > 0 )
        {
        targetDeps[realTargetName] = 1;
        }
      for ( llit = ll->begin(); llit != ll->end(); ++ llit )
        {
        const char* libName = llit->first.c_str();
        std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);
        if ( ignoreTargetsSet.find(libName) != ignoreTargetsSet.end() )
          {
          // Skip ignored targets
          continue;
          }
        if ( tarIt == targetNamesNodes.end() )
          {
          sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
          targetDeps[libName] = 2;
          targetNamesNodes[libName] = tgtName;
          //str << "    \"" << tgtName << "\" [ label=\"" << libName <<  "\" shape=\"ellipse\"];" << std::endl;

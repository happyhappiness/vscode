          sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
          targetDeps[libName] = 2;
          targetNamesNodes[libName] = tgtName;
          //str << "    \"" << tgtName << "\" [ label=\"" << libName
          //<<  "\" shape=\"ellipse\"];" << std::endl;
          }
        else
          {
          std::map<cmStdString, int>::iterator depIt
            = targetDeps.find(libName);
          if ( depIt == targetDeps.end() )
            {
            targetDeps[libName] = 1;

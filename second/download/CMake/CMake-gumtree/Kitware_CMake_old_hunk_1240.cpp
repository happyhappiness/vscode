    cmTargets::iterator tit;
    for ( tit = targets->begin(); tit != targets->end(); ++ tit )
      {
      //std::cout << "Found target: " << tit->first.c_str() << std::endl;
      sprintf(tgtName, "node%d", cnt++);
      targetNamesNodes[tit->first.c_str()] = tgtName;
      targetPtrs[tit->first.c_str()] = &tit->second;
      //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str() <<  "\" shape=\"box\"];" << std::endl;
      }
    }

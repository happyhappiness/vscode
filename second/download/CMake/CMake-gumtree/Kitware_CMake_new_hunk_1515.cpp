      sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);

      targetNamesNodes[realTargetName] = tgtName;

      targetPtrs[realTargetName] = &tit->second;

      //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str()

      //<<  "\" shape=\"box\"];" << std::endl;

      }

    }

  // Ok, now find all the stuff we link to that is not in cmake


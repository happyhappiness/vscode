    cmTargets::iterator tit;

    for ( tit = targets->begin(); tit != targets->end(); ++ tit )

      {

      const char* realTargetName = tit->first.c_str();

      if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )

        {

        // Skip ignored targets

        continue;

        }

      //std::cout << "Found target: " << tit->first.c_str() << std::endl;

      sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);

      targetNamesNodes[realTargetName] = tgtName;

      targetPtrs[realTargetName] = &tit->second;

      //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str() <<  "\" shape=\"box\"];" << std::endl;

      }

    }


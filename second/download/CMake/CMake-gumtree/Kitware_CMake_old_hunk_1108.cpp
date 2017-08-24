        continue;
        }
      //std::cout << "Found target: " << tit->first.c_str() << std::endl;
      sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
      targetNamesNodes[realTargetName] = tgtName;
      targetPtrs[realTargetName] = &tit->second;
      }
    }

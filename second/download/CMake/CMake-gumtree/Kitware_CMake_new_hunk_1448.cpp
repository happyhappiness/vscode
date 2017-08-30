        continue;

        }

      //std::cout << "Found target: " << tit->first.c_str() << std::endl;

      cmOStringStream ostr;

      ostr << graphNodePrefix << cnt++;

      targetNamesNodes[realTargetName] = ostr.str();

      targetPtrs[realTargetName] = &tit->second;

      }

    }


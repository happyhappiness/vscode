void cmake::GenerateGraphViz(const char* fileName)
{
  cmGeneratedFileStream str(fileName);
  if ( !str )
    {
    return;
    }
  str << "digraph G {" << std::endl;
  str << "node [" << std::endl;
  str << "  fontsize = \"12\"" << std::endl;
  str << "];" << std::endl;

  cmGlobalGenerator* gg = this->GetGlobalGenerator();
  std::vector<cmLocalGenerator*> localGenerators;
  gg->GetLocalGenerators(localGenerators);
  std::vector<cmLocalGenerator*>::iterator lit;
  // for target deps
  // 1 - cmake target
  // 2 - external target
  // 0 - no deps
  std::map<cmStdString, int> targetDeps;
  std::map<cmStdString, cmTarget*> targetPtrs;
  std::map<cmStdString, cmStdString> targetNamesNodes;
  char tgtName[100];
  int cnt = 0;
  // First pass get the list of all cmake targets
  for ( lit = localGenerators.begin(); lit != localGenerators.end(); ++ lit )
    {
    cmTargets* targets = &((*lit)->GetMakefile()->GetTargets());
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
  // Ok, now find all the stuff we link to that is not in cmake
  for ( lit = localGenerators.begin(); lit != localGenerators.end(); ++ lit )
    {
    cmTargets* targets = &((*lit)->GetMakefile()->GetTargets());
    cmTargets::iterator tit;
    for ( tit = targets->begin(); tit != targets->end(); ++ tit )
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
          }
        else
          {
          std::map<cmStdString, int>::iterator depIt = targetDeps.find(libName);
          if ( depIt == targetDeps.end() )
            {
            targetDeps[libName] = 1;
            }
          }
        }
      }
    }

  // Write out nodes
  std::map<cmStdString, int>::iterator depIt;
  for ( depIt = targetDeps.begin(); depIt != targetDeps.end(); ++ depIt )
    {
    const char* newTargetName = depIt->first.c_str();
    std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(newTargetName);
    if ( tarIt == targetNamesNodes.end() )
      {
      // We should not be here.
      std::cout << "Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
      abort();
      }

    str << "    \"" << tarIt->second.c_str() << "\" [ label=\"" << newTargetName <<  "\" shape=\"";
    if ( depIt->second == 1 )
      {
      std::map<cmStdString, cmTarget*>::iterator tarTypeIt= targetPtrs.find(newTargetName);
      if ( tarTypeIt == targetPtrs.end() )
        {
        // We should not be here.
        std::cout << "Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
        abort();
        }
      cmTarget* tg = tarTypeIt->second;
      switch ( tg->GetType() )
        {
      case cmTarget::EXECUTABLE:
        str << "house";
        break;
      case cmTarget::STATIC_LIBRARY:
        str << "diamond";
        break;
      case cmTarget::SHARED_LIBRARY:
        str << "polygon";
        break;
      case cmTarget::MODULE_LIBRARY:
        str << "octagon";
        break;
      default:
        str << "box";
        }
      }
    else
      {
      str << "ellipse";
      }
    str << "\"];" << std::endl;
    }

  // Now generate the connectivity
  for ( lit = localGenerators.begin(); lit != localGenerators.end(); ++ lit )
    {
    cmTargets* targets = &((*lit)->GetMakefile()->GetTargets());
    cmTargets::iterator tit;
    for ( tit = targets->begin(); tit != targets->end(); ++ tit )
      {
      std::map<cmStdString, int>::iterator dependIt = targetDeps.find(tit->first.c_str());
      if ( dependIt == targetDeps.end() )
        {
        continue;
        }
      std::map<cmStdString, cmStdString>::iterator cmakeTarIt = targetNamesNodes.find(tit->first.c_str());
      const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());
      cmTarget::LinkLibraries::const_iterator llit;
      for ( llit = ll->begin(); llit != ll->end(); ++ llit )
        {
        const char* libName = llit->first.c_str();
        std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);
        if ( tarIt == targetNamesNodes.end() )
          {
          // We should not be here.
          std::cout << "Cannot find library: " << libName << " even though it was added in the previous pass" << std::endl;
          abort();
          }
        str << "    \"" << cmakeTarIt->second.c_str() << "\" -> \"" << tarIt->second.c_str() << "\"" << std::endl;
        }
      }
    }

  // TODO: Use dotted or something for external libraries
  //str << "    \"node0\":f4 -> \"node12\"[color=\"#0000ff\" style=dotted]" << std::endl;
  //
  str << "}" << std::endl;
}
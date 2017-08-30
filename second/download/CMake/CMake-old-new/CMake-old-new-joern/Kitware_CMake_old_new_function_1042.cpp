int cmake::getAllExternalLibs(const std::set<cmStdString>& ignoreTargetsSet,
                          std::map<cmStdString, cmStdString>& targetNamesNodes,
                          std::map<cmStdString, const cmTarget*>& targetPtrs,
                          std::map<cmStdString, int>& targetDeps,
                          const char* graphNodePrefix) const
{
  int cnt = 0;

  const std::vector<cmLocalGenerator*>& localGenerators =
                              this->GetGlobalGenerator()->GetLocalGenerators();
  // Ok, now find all the stuff we link to that is not in cmake
  for (std::vector<cmLocalGenerator*>::const_iterator lit =
                                                       localGenerators.begin();
       lit != localGenerators.end();
       ++ lit )
    {
    const cmTargets* targets = &((*lit)->GetMakefile()->GetTargets());
    for ( cmTargets::const_iterator tit = targets->begin();
          tit != targets->end();
          ++ tit )
      {
      const char* realTargetName = tit->first.c_str();
      if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
        {
        // Skip ignored targets
        continue;
        }
      const cmTarget::LinkLibraryVectorType* ll =
                                     &(tit->second.GetOriginalLinkLibraries());
      if ( ll->size() > 0 )
        {
        targetDeps[realTargetName] = DOT_DEP_TARGET;
        fprintf(stderr, " + %s\n", realTargetName);
        }
      for (cmTarget::LinkLibraryVectorType::const_iterator llit = ll->begin();
           llit != ll->end();
           ++ llit )
        {
        const char* libName = llit->first.c_str();
        if ( ignoreTargetsSet.find(libName) != ignoreTargetsSet.end() )
          {
          // Skip ignored targets
          continue;
          }

        std::map<cmStdString, cmStdString>::const_iterator tarIt =
                                                targetNamesNodes.find(libName);
        if ( tarIt == targetNamesNodes.end() )
          {
          cmOStringStream ostr;
          ostr << graphNodePrefix << cnt++;
          targetDeps[libName] = DOT_DEP_EXTERNAL;
          targetNamesNodes[libName] = ostr.str();
          //str << "    \"" << ostr.c_str() << "\" [ label=\"" << libName
          //<<  "\" shape=\"ellipse\"];" << std::endl;
          }
        else
          {
          std::map<cmStdString, int>::const_iterator depIt =
                                                      targetDeps.find(libName);
          if ( depIt == targetDeps.end() )
            {
            targetDeps[libName] = DOT_DEP_TARGET;
            }
          }
        }
      }
    }
   return cnt;
}
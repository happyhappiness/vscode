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


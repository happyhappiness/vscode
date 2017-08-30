{
          sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
          targetDeps[libName] = 2;
          targetNamesNodes[libName] = tgtName;
          //str << "    \"" << tgtName << "\" [ label=\"" << libName
          //<<  "\" shape=\"ellipse\"];" << std::endl;
          }
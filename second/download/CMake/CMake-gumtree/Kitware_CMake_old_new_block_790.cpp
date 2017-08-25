{
          sprintf(tgtName, "node%d", cnt++);
          targetDeps[libName] = 2;
          targetNamesNodes[libName] = tgtName;
          //str << "    \"" << tgtName << "\" [ label=\"" << libName <<  "\" shape=\"ellipse\"];" << std::endl;
          }
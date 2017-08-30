          }
        if ( tarIt == targetNamesNodes.end() )
          {
          cmOStringStream ostr;
          ostr << graphNodePrefix << cnt++;
          targetDeps[libName] = 2;
          targetNamesNodes[libName] = ostr.str();
          //str << "    \"" << ostr.c_str() << "\" [ label=\"" << libName
          //<<  "\" shape=\"ellipse\"];" << std::endl;
          }
        else
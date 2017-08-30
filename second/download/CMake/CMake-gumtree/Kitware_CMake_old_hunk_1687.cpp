        hex[0] = c;
        switch ( c )
          {
          case '+':
          case '?':
          case '/':
          case '\\':
          case '&':
          case ' ':
          case '=':
          case '%':
            sprintf(hex, "%%%02X", (int)c);
            ofile.append(hex);
            break;
          default: 
            ofile.append(hex);
          }
        }
      std::string upload_as = url + "?FileName=" + ofile;

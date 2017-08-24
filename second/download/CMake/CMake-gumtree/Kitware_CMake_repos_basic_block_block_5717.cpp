{
          failf(data, "Syntax error in telnet option: %s", head->data);
          result = CURLE_TELNET_OPTION_SYNTAX;
          break;
        }
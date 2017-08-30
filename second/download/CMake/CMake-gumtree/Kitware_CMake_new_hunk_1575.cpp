        case ' ':

        case '=':

        case '%':

          sprintf(hexCh, "%%%02X", (int)c);

          ofile.append(hexCh);

          break;

        default: 

          ofile.append(hexCh);

          }

        }

      cmStdString turl 


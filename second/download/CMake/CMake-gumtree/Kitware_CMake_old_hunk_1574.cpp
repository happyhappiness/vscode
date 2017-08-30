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

      cmStdString upload_as 


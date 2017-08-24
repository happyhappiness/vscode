(*c) {
          case '<':
            fprintf(fout, "&lt;");
            break;
          case '>':
            fprintf(fout, "&gt;");
            break;
          case '&':
            fprintf(fout, "&amp;");
            break;
          default:
            putc(*c, fout);
            break;
        }
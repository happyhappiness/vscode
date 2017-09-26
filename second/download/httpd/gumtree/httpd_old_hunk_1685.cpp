    case OP_TYPEQUERY:
    case OP_TYPEMINQUERY:
    fprintf(f, "    ");
    if (*code >= OP_TYPESTAR)
      {
      fprintf(f, "%s", OP_names[code[1]]);
      if (code[1] == OP_PROP || code[1] == OP_NOTPROP)
        {
        fprintf(f, " %s ", get_ucpname(code[2]));
        extra = 1;
        }
      }
    else extra = print_char(f, code+1, utf8);
    fprintf(f, "%s", OP_names[*code]);
    break;

    case OP_EXACT:

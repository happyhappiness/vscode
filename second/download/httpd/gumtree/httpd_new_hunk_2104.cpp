    break;

    case OP_TYPEEXACT:
    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    fprintf(f, "    %s", OP_names[code[3]]);
#ifdef SUPPORT_UCP
    if (code[3] == OP_PROP || code[3] == OP_NOTPROP)
      {
      fprintf(f, " %s ", get_ucpname(code[4]));
      extra = 1;
      }
#endif
    fprintf(f, "{");
    if (*code != OP_TYPEEXACT) fprintf(f, "0,");
    fprintf(f, "%d}", GET2(code,1));
    if (*code == OP_TYPEMINUPTO) fprintf(f, "?");
    break;


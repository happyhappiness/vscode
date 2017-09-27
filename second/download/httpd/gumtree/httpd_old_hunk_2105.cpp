
    case OP_CALLOUT:
    fprintf(f, "    %s %d %d %d", OP_names[*code], code[1], GET(code,2),
      GET(code, 2 + LINK_SIZE));
    break;

    case OP_PROP:
    case OP_NOTPROP:
    fprintf(f, "    %s %s", OP_names[*code], get_ucpname(code[1]));
    break;

    /* OP_XCLASS can only occur in UTF-8 mode. However, there's no harm in
    having this code always here, and it makes it less messy without all those
    #ifdefs. */

    case OP_CLASS:

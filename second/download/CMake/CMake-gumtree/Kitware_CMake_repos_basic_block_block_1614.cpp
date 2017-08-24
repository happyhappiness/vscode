{
      case BOL:
        if (reginput != regbol)
          return (0);
        break;
      case EOL:
        if (*reginput != '\0')
          return (0);
        break;
      case ANY:
        if (*reginput == '\0')
          return (0);
        reginput++;
        break;
      case EXACTLY: {
        size_t len;
        const char* opnd;

        opnd = OPERAND(scan);
        // Inline the first character, for speed.
        if (*opnd != *reginput)
          return (0);
        len = strlen(opnd);
        if (len > 1 && strncmp(opnd, reginput, len) != 0)
          return (0);
        reginput += len;
      } break;
      case ANYOF:
        if (*reginput == '\0' || strchr(OPERAND(scan), *reginput) == 0)
          return (0);
        reginput++;
        break;
      case ANYBUT:
        if (*reginput == '\0' || strchr(OPERAND(scan), *reginput) != 0)
          return (0);
        reginput++;
        break;
      case NOTHING:
        break;
      case BACK:
        break;
      case OPEN + 1:
      case OPEN + 2:
      case OPEN + 3:
      case OPEN + 4:
      case OPEN + 5:
      case OPEN + 6:
      case OPEN + 7:
      case OPEN + 8:
      case OPEN + 9: {
        int no;
        const char* save;

        no = OP(scan) - OPEN;
        save = reginput;

        if (regmatch(next)) {

          //
          // Don't set startp if some later invocation of the
          // same parentheses already has.
          //
          if (regstartp[no] == 0)
            regstartp[no] = save;
          return (1);
        } else
          return (0);
      }
      //              break;
      case CLOSE + 1:
      case CLOSE + 2:
      case CLOSE + 3:
      case CLOSE + 4:
      case CLOSE + 5:
      case CLOSE + 6:
      case CLOSE + 7:
      case CLOSE + 8:
      case CLOSE + 9: {
        int no;
        const char* save;

        no = OP(scan) - CLOSE;
        save = reginput;

        if (regmatch(next)) {

          //
          // Don't set endp if some later invocation of the
          // same parentheses already has.
          //
          if (regendp[no] == 0)
            regendp[no] = save;
          return (1);
        } else
          return (0);
      }
      //              break;
      case BRANCH: {

        const char* save;

        if (OP(next) != BRANCH) // No choice.
          next = OPERAND(scan); // Avoid recursion.
        else {
          do {
            save = reginput;
            if (regmatch(OPERAND(scan)))
              return (1);
            reginput = save;
            scan = regnext(scan);
          } while (scan != 0 && OP(scan) == BRANCH);
          return (0);
          // NOTREACHED
        }
      } break;
      case STAR:
      case PLUS: {
        char nextch;
        int no;
        const char* save;
        int min_no;

        //
        // Lookahead to avoid useless match attempts when we know
        // what character comes next.
        //
        nextch = '\0';
        if (OP(next) == EXACTLY)
          nextch = *OPERAND(next);
        min_no = (OP(scan) == STAR) ? 0 : 1;
        save = reginput;
        no = regrepeat(OPERAND(scan));
        while (no >= min_no) {
          // If it could work, try it.
          if (nextch == '\0' || *reginput == nextch)
            if (regmatch(next))
              return (1);
          // Couldn't or didn't -- back up.
          no--;
          reginput = save + no;
        }
        return (0);
      }
      //              break;
      case END:
        return (1); // Success!

      default:
        // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
        printf(
          "RegularExpression::find(): Internal error -- memory corrupted.\n");
        return 0;
    }
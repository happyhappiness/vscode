do {
            save = reginput;
            if (regmatch(OPERAND(scan)))
              return (1);
            reginput = save;
            scan = regnext(scan);
          } while (scan != 0 && OP(scan) == BRANCH);
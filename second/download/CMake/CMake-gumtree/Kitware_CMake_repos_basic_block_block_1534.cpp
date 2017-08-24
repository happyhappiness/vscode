(OP(scan) == EXACTLY && strlen(OPERAND(scan)) >= len) {
          longest = OPERAND(scan);
          len = strlen(OPERAND(scan));
        }
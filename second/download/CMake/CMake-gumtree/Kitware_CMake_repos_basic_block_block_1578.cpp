{
            rxpclass = UCHARAT(regparse - 2) + 1;
            rxpclassend = UCHARAT(regparse);
            if (rxpclass > rxpclassend + 1) {
              // RAISE Error, SYM(RegularExpression), SYM(Invalid_Range),
              printf("RegularExpression::compile(): Invalid range in [].\n");
              return 0;
            }
            for (; rxpclass <= rxpclassend; rxpclass++)
              regc(static_cast<char>(rxpclass));
            regparse++;
          }
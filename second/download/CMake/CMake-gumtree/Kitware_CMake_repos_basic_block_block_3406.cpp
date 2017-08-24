(i = 0; i < 16; i++) {
          inUse16[i] = False;
          for (j = 0; j < 16; j++)
             if (s->inUse[i * 16 + j]) inUse16[i] = True;
      }
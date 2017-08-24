(cp->PipeReadEnds[i] >= 0) {
      FD_SET(cp->PipeReadEnds[i], &cp->PipeSet);
      if (cp->PipeReadEnds[i] > max) {
        max = cp->PipeReadEnds[i];
      }
    }
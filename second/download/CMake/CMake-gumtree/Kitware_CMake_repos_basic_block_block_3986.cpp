r(i=0; i < data->state.tempcount; i++) {
      writebuf[i] = data->state.tempwrite[i];
      data->state.tempwrite[i].buf = NULL;
    }
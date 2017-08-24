r(i=0; i < data->state.tempcount; i++) {
    free(data->state.tempwrite[i].buf);
  }
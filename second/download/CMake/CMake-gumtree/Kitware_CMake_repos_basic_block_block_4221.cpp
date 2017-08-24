f(!stream->closed) {
      DEBUGASSERT(httpc->drain_total >= data->state.drain);
      httpc->drain_total -= data->state.drain;
      data->state.drain = 0; /* this stream is hereby drained */
    }
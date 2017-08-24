f(si != nread) {
    /* Upload from the new (replaced) buffer instead */
    data->req.upload_fromhere = scratch;

    /* Save the buffer so it can be freed later */
    data->state.scratch = scratch;

    /* Free the old scratch buffer */
    free(oldscratch);

    /* Set the new amount too */
    data->req.upload_present = si;
  }
  else
    free(newscratch)
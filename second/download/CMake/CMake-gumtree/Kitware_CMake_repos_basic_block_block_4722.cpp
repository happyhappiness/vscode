{
    /* Set connection owner so that the DONE function closes it.  We can
       safely do this here since connection is killed. */
    data->easy_conn->data = easy;
    /* If the handle is in a pipeline and has started sending off its
       request but not received its response yet, we need to close
       connection. */
    streamclose(data->easy_conn, "Removed with partial response");
    easy_owns_conn = TRUE;
  }
static void clean_fifo(GlobalInfo *g)
{
    event_free(g->fifo_event);
    fclose(g->input);
    unlink(fifo);
}
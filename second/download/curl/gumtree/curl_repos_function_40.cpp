void pgrsDone(struct UrlData *data)
{
  if(!(data->progress.flags & PGRS_HIDE)) {
    data->progress.lastshow=0;
    pgrsUpdate(data); /* the final (forced) update */
    fprintf(stderr, "\n");
  }
}
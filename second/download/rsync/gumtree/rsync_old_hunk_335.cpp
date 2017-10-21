extern int ignore_times;
extern int recurse;
extern int delete_mode;
extern int cvs_exclude;
extern int am_root;
extern int relative_paths;

/*
  free a sums struct
  */
static void free_sums(struct sum_struct *s)
{
  if (s->sums) free(s->sums);
  free(s);
}



/*
  send a sums struct down a fd
  */
static void send_sums(struct sum_struct *s,int f_out)
{

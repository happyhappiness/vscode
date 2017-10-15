#define CURHDR Context->hdrs[Context->v2r[menu->current]]
#define OLDHDR Context->hdrs[Context->v2r[menu->oldcurrent]]
#define UNREAD(h) mutt_thread_contains_unread (Context, h)

extern size_t UngetCount;

void index_make_entry (char *s, size_t l, MUTTMENU *menu, int num)
{
  format_flag flag = M_FORMAT_MAKEPRINT | M_FORMAT_ARROWCURSOR | M_FORMAT_INDEX;
  int edgemsgno, reverse = Sort & SORT_REVERSE;
  HEADER *h = Context->hdrs[Context->v2r[num]];
  THREAD *tmp;

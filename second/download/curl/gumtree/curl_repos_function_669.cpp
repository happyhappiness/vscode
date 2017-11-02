static void AppendNode(struct multi_files **first,
                       struct multi_files **last,
                       struct multi_files  *new)
{
  DEBUGASSERT(((*first) && (*last)) || ((!*first) && (!*last)));

  if(*last)
    (*last)->next = new;
  else
    *first = new;
  *last = new;
}
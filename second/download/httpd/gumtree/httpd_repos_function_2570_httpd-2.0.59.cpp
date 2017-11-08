static
void hashTableInit(HASH_TABLE *p, XML_Memory_Handling_Suite *ms)
{
  p->size = 0;
  p->usedLim = 0;
  p->used = 0;
  p->v = 0;
  p->mem = ms;
}
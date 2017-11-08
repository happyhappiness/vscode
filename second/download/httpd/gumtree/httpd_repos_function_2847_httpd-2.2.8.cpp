static
void poolInit(STRING_POOL *pool, XML_Memory_Handling_Suite *ms)
{
  pool->blocks = 0;
  pool->freeBlocks = 0;
  pool->start = 0;
  pool->ptr = 0;
  pool->end = 0;
  pool->mem = ms;
}
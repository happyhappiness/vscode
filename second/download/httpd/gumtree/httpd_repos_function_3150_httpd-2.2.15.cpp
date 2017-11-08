static int
nextScaffoldPart(XML_Parser parser)
{
  CONTENT_SCAFFOLD * me;
  int next;

  if (! dtd.scaffIndex) {
    dtd.scaffIndex = MALLOC(groupSize * sizeof(int));
    if (! dtd.scaffIndex)
      return -1;
    dtd.scaffIndex[0] = 0;
  }

  if (dtd.scaffCount >= dtd.scaffSize) {
    if (dtd.scaffold) {
      dtd.scaffSize *= 2;
      dtd.scaffold = (CONTENT_SCAFFOLD *) REALLOC(dtd.scaffold,
					      dtd.scaffSize * sizeof(CONTENT_SCAFFOLD));
    }
    else {
      dtd.scaffSize = 32;
      dtd.scaffold = (CONTENT_SCAFFOLD *) MALLOC(dtd.scaffSize * sizeof(CONTENT_SCAFFOLD));
    }
    if (! dtd.scaffold)
      return -1;
  }
  next = dtd.scaffCount++;
  me = &dtd.scaffold[next];
  if (dtd.scaffLevel) { 
    CONTENT_SCAFFOLD *parent = &dtd.scaffold[dtd.scaffIndex[dtd.scaffLevel - 1]];
    if (parent->lastchild) {
      dtd.scaffold[parent->lastchild].nextsib = next;
    }
    if (! parent->childcnt)
      parent->firstchild = next;
    parent->lastchild = next;
    parent->childcnt++;
  }
  me->firstchild = me->lastchild = me->childcnt = me->nextsib = 0;
  return next;
}
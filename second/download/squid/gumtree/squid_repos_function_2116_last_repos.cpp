void
debugObj(int section, int level, const char *label, void *obj, ObjPackMethod pm)
{
    assert(label && obj && pm);
    MemBuf mb;
    mb.init();
    (*pm) (obj, &mb);
    debugs(section, level, "" << label << "" << mb.buf << "");
    mb.clean();
}
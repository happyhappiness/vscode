void
debugObj(int section, int level, const char *label, void *obj, ObjPackMethod pm)
{
    MemBuf mb;
    Packer p;
    assert(label && obj && pm);
    mb.init();
    packerToMemInit(&p, &mb);
    (*pm) (obj, &p);
    debugs(section, level, "" << label << "" << mb.buf << "");
    packerClean(&p);
    mb.clean();
}
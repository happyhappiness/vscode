static void
free_external_acl_data(void *data)
{
    external_acl_data *p = static_cast<external_acl_data *>(data);
    wordlistDestroy(&p->arguments);
    cbdataReferenceDone(p->def);
}
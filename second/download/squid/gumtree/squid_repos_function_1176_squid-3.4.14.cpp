static void
free_PortCfg(AnyP::PortCfg ** head)
{
    AnyP::PortCfg *s;

    while ((s = *head) != NULL) {
        *head = s->next;
        cbdataReferenceDone(s);
    }
}
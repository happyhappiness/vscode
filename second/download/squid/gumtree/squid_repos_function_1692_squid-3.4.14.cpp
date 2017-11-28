void
HttpHdrSc::updateStats(StatHist * hist) const
{
    dlink_node *sct = targets.head;

    while (sct) {
        static_cast<HttpHdrScTarget *>(sct->data)->updateStats(hist);
        sct = sct->next;
    }
}
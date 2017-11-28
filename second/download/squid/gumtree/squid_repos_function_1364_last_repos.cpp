HttpHdrScTarget *
HttpHdrSc::findTarget(const char *target)
{
    dlink_node *node;
    node = targets.head;

    while (node) {
        HttpHdrScTarget *sct = (HttpHdrScTarget *)node->data;

        if (target && sct->target.size() > 0 && !strcmp(target, sct->target.termedBuf()))
            return sct;
        else if (!target && sct->target.size() == 0)
            return sct;

        node = node->next;
    }

    return NULL;
}
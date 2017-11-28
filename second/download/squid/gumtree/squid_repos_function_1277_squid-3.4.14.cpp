void
StoreMeta::FreeList(StoreMeta **head)
{
    StoreMeta *node;

    while ((node = *head) != NULL) {
        *head = node->next;
        xfree(node->value);
        delete node;
    }
}
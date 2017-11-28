StoreMeta **
StoreMeta::Add(StoreMeta **tail, StoreMeta *aNode)
{
    assert (*tail == NULL);
    *tail = aNode;
    return &aNode->next;		/* return new tail pointer */
}
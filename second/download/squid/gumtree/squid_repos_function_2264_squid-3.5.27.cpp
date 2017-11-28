mem_node *
mem_hdr::nodeToRecieve(int64_t offset)
{
    /* case 1: Nothing in memory */

    if (!nodes.size()) {
        appendNode (new mem_node(offset));
        return nodes.start()->data;
    }

    mem_node *candidate = NULL;
    /* case 2: location fits within an extant node */

    if (offset > 0) {
        mem_node search (offset - 1);
        search.nodeBuffer.length = 1;
        mem_node *const *leadup =  nodes.find (&search, NodeCompare);

        if (leadup)
            candidate = *leadup;
    }

    if (candidate && candidate->canAccept(offset))
        return candidate;

    /* candidate can't accept, so we need a new node */
    candidate = new mem_node(offset);

    appendNode (candidate);

    /* simpler to write than a indented if */
    return candidate;
}
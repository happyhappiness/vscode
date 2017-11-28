int
verify_heap_property(heap * hp)
{
    int i = 0;
    int correct = 1;
    for (i = 0; i < hp->last / 2; i++) {
        correct = 1;
        if (_heap_node_exist(hp, Left(i)))
            if (hp->nodes[i]->key > hp->nodes[Left(i)]->key)
                correct = 0;
        if (_heap_node_exist(hp, Right(i)))
            if (hp->nodes[i]->key > hp->nodes[Right(i)]->key)
                correct = 0;
        if (!correct) {
            printf("verifyHeap: violated at %d", i);
            heap_print_inorder(hp, 0);
            break;
        }
    }
    return correct;
}
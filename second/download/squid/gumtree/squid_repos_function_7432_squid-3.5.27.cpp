static void
heap_print_inorder(heap * hp, int id)
{
    while (id < hp->last) {
        printf("%d\tKey = %.04f\n", id, hp->nodes[id]->key);
        id++;
    }
}
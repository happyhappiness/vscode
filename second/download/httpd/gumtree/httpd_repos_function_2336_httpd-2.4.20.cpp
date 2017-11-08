static void tq_swap(h2_int_queue *q, int i, int j)
{
    int x = q->elts[i];
    q->elts[i] = q->elts[j];
    q->elts[j] = x;
}
static void
destroyRadixNodeInfo(as_info * e_info)
{
    CbDataList<int> *prev = NULL;
    CbDataList<int> *data = e_info->as_number;

    while (data) {
        prev = data;
        data = data->next;
        delete prev;
    }
}
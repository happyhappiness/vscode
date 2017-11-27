static void direct_list_free(void)
{
    direct_access_element_t *traverse = direct_list;
    direct_access_element_t *tmp = NULL;;

    while(traverse != NULL)
    {
        tmp = traverse;
        traverse = traverse->next;
        direct_list_element_free (tmp);
        tmp = NULL;
    }
}
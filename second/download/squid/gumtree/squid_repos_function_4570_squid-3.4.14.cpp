void
ACLIP::parse()
{
    flags.parseFlags();

    while (char *t = strtokFile()) {
        acl_ip_data *q = acl_ip_data::FactoryParse(t);

        while (q != NULL) {
            /* pop each result off the list and add it to the data tree individually */
            acl_ip_data *next_node = q->next;
            q->next = NULL;
            data = data->insert(q, acl_ip_data::NetworkCompare);
            q = next_node;
        }
    }
}
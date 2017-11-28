void
ACLIP::parse()
{
    if (data == NULL)
        data = new IPSplay();

    while (char *t = ConfigParser::strtokFile()) {
        acl_ip_data *q = acl_ip_data::FactoryParse(t);

        while (q != NULL) {
            /* pop each result off the list and add it to the data tree individually */
            acl_ip_data *next_node = q->next;
            q->next = NULL;
            if (!data->find(q,acl_ip_data::NetworkCompare))
                data->insert(q, acl_ip_data::NetworkCompare);
            q = next_node;
        }
    }
}
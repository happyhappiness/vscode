        type = get_token(fp, token);
        if (type != LABEL) {
            if (type == ENDOFFILE) {
                return root;
            }
            print_error(token, "is a reserved word", type);
            free_node_list(root);
            return NULL;
        }
        strncpy(name, token, 64);
        name[63] = '\0';
        type = get_token(fp, token);
        if (type == OBJTYPE) {
            if (root == NULL) {
                /* first link in chain */
                np = root = parse_objecttype(fp, name);
                if (np == NULL) {

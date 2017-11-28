void operator() (const acl_httpstatus_data * node) {
        contents.push_back(node->toStr());
    }
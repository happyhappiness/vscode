            l->delAt(p, headers_deleted);

    if (headers_deleted)
        l->refreshMask();
}

/**
 * return 1 if manglers are configured.  Used to set a flag
 * for optimization during request forwarding.
 */
int
httpReqHdrManglersConfigured()
{
    for (int i = 0; i < HDR_ENUM_END; i++) {
        if (NULL != Config.request_header_access[i].access_list)
            return 1;
    }

    return 0;
}

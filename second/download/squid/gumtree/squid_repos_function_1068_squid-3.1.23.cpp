static const char *
peer_type_str(const peer_t type)
{
    const char * result;

    switch (type) {

    case PEER_PARENT:
        result = "parent";
        break;

    case PEER_SIBLING:
        result = "sibling";
        break;

    case PEER_MULTICAST:
        result = "multicast";
        break;

    default:
        result = "unknown";
        break;
    }

    return result;
}
    if (status == APR_SUCCESS && !*peos && !*plen) {
        return APR_EAGAIN;
    }
    return status;
}


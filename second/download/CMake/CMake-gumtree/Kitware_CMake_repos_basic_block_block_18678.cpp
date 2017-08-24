{
        l_cur = ifa;
        ifa = ifa->ifa_next;
        uv__free(l_cur);
    }
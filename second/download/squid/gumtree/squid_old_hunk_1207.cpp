    }
#elif _SQUID_LINUX_
    Ip::Interceptor.StopTransparency("Missing needed capability support.");
#endif /* HAVE_SYS_CAPABILITY_H */
}


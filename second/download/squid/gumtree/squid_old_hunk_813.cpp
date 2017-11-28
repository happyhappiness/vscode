        return htcpBuildSpecifier(buf, buflen, stuff);

    case RR_RESPONSE:
        debugs(31, 3, "htcpBuildTstOpData: RR_RESPONSE");
        debugs(31, 3, "htcpBuildTstOpData: F1 = " << stuff->f1);

        if (stuff->f1)		/* cache miss */
            return 0;
        else			/* cache hit */
            return htcpBuildDetail(buf, buflen, stuff);

    default:
        fatal_dump("htcpBuildTstOpData: bad RR value");
    }


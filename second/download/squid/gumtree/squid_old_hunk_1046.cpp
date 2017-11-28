                delete detail_mb;
                do_quote = 0;
            }
        }
#endif
        if (!mb.contentSize())
            mb.Printf("[No Error Detail]");
        break;

    case 'e':
        mb.Printf("%d", xerrno);
        break;

    case 'E':
        if (xerrno)
            mb.Printf("(%d) %s", xerrno, strerror(xerrno));
        else
            mb.Printf("[No Error]");
        break;

    case 'f':
        if (building_deny_info_url) break;
        /* FTP REQUEST LINE */
        if (ftp.request)

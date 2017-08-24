{
        case 0x00:
          break;
        case 0x01:
          STORE_TLBCACHE_INFO(TLBCode, 4);
          break;
        case 0x02:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x03:
          STORE_TLBCACHE_INFO(TLBData, 4);
          break;
        case 0x04:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x06:
          STORE_TLBCACHE_INFO(L1Code, 8);
          break;
        case 0x08:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break;
        case 0x0a:
          STORE_TLBCACHE_INFO(L1Data, 8);
          break;
        case 0x0c:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break;
        case 0x10:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x15:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x1a:
          STORE_TLBCACHE_INFO(L2Unified, 96);
          break; // <-- FIXME: IA-64 Only
        case 0x22:
          STORE_TLBCACHE_INFO(L3Unified, 512);
          break;
        case 0x23:
          STORE_TLBCACHE_INFO(L3Unified, 1024);
          break;
        case 0x25:
          STORE_TLBCACHE_INFO(L3Unified, 2048);
          break;
        case 0x29:
          STORE_TLBCACHE_INFO(L3Unified, 4096);
          break;
        case 0x39:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x3c:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x40:
          STORE_TLBCACHE_INFO(L2Unified, 0);
          break; // <-- FIXME: No integrated L2 cache (P6 core) or L3 cache (P4
                 // core).
        case 0x41:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x42:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x43:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x44:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x45:
          STORE_TLBCACHE_INFO(L2Unified, 2048);
          break;
        case 0x50:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x51:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x52:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x5b:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x5c:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x5d:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x66:
          STORE_TLBCACHE_INFO(L1Data, 8);
          break;
        case 0x67:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break;
        case 0x68:
          STORE_TLBCACHE_INFO(L1Data, 32);
          break;
        case 0x70:
          STORE_TLBCACHE_INFO(L1Trace, 12);
          break;
        case 0x71:
          STORE_TLBCACHE_INFO(L1Trace, 16);
          break;
        case 0x72:
          STORE_TLBCACHE_INFO(L1Trace, 32);
          break;
        case 0x77:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x79:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x7a:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x7b:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x7c:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x7e:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x81:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x82:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x83:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x84:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x85:
          STORE_TLBCACHE_INFO(L2Unified, 2048);
          break;
        case 0x88:
          STORE_TLBCACHE_INFO(L3Unified, 2048);
          break; // <-- FIXME: IA-64 Only
        case 0x89:
          STORE_TLBCACHE_INFO(L3Unified, 4096);
          break; // <-- FIXME: IA-64 Only
        case 0x8a:
          STORE_TLBCACHE_INFO(L3Unified, 8192);
          break; // <-- FIXME: IA-64 Only
        case 0x8d:
          STORE_TLBCACHE_INFO(L3Unified, 3096);
          break; // <-- FIXME: IA-64 Only
        case 0x90:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only
        case 0x96:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only
        case 0x9b:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only

        // Default case - an error has occurred.
        default:
          return false;
      }
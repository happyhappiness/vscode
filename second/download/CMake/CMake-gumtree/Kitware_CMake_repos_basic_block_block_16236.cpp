(u16[u16len-2] == 0 &&
			    (u16[u16len-1] == '/' || u16[u16len-1] == '\\'))
#else
			if (u16[u16len-2] == 0 && u16[u16len-1] == '/')
#endif
			{
				u16len -= 2;
			} else
				break;
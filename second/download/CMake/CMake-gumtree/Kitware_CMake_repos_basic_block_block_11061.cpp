{
				int next;
				if ((next = find_cab_magic(p)) == 0)
					return (64);
				p += next;
			}
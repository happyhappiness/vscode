{
		struct xattr *next;

		next = xattr->next;
		xattr_free(xattr);
		xattr = next;
	}
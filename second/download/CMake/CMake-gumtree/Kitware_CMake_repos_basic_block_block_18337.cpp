{
		const char* src = (const char*)from;
		for (length += index; (size_t)index < length; index++) ((char*)to)[index ^ 3] = *(src++);
	}
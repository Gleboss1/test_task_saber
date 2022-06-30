//task 2

void RemoveDups(char* pStr)
{
	if (*pStr == 0) return;

	char* result = pStr;

	for (char* pRead = pStr; *pRead != 0; ++pRead)
	{
		if (*pRead == *result)
		{
			continue;
		}
		*(++result) = *pRead;
	}

	*(result + 1) = 0;
}
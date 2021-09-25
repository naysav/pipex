#include <stdio.h>

int	str_ncmp (char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++; 
		str2++;
        printf("aft s1 %c\n", *str1);
        printf("aft s2 %c\n", *str2);
	}
	return (*str2 - *str1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s2 != *(unsigned char *)s1)
			return ((int)(*(unsigned char *)s1 - *(unsigned char *)s2));
		if (!(*(unsigned char *)s2) || !(*(unsigned char *)s1))
			return ((int)(*(unsigned char *)s1 - *(unsigned char *)s2));
		s1++;
		s2++;
	}
	return (0);
}


int main() {
    printf("1 %d\n", ft_strncmp("12345c", "1234", 5));
    printf("2 %d\n", str_ncmp("1234", "12345c", 5));
}

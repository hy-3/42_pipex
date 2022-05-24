#include "../src/pipex.h"

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	total_len;
	unsigned int	i;
	unsigned int	k;
	char			*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] > 0)
		res[k++] = s1[i++];
	i = 0;
	while (s2[i] > 0)
		res[k++] = s2[i++];
	res[k] = '\0';
	return (res);
}
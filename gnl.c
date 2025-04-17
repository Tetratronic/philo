#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define	BS 1024

char	*get_line(char *rem)
{
	ssize_t	pos;
	char	*res;
	int		i;

	pos = strchr(rem, '\n') - rem;
	res = malloc(pos + 2);
	if (!res)
		return NULL;
	i = 0;
	while (*rem != '\n')
		res[i++] = *rem++;
	res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

char *strjoin(const char* str1, const char* str2) {
    if (str1 == NULL && str2 == NULL) {
        return NULL;
    }
	if (!str1)
		return (strdup(str2));
	if (!str2)
		return (strdup(str1));
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)malloc(len1 + len2 + 1);
    
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char	*keep_rem(char **rem)
{
	char	*res;
	ssize_t	nl;

	nl = strchr(*rem, '\n') - *rem;
	res = strdup(*rem + nl + 1);
	if (!res)
		return (NULL);
	free(*rem);
	return (res);
}

char *check_rem(char **rem)
{
    char *temp;
    if (*rem)
    {
        temp = strdup(*rem);
        free(*rem);
        *rem = NULL;
    }
    else
        temp = NULL;
    return (temp);
}

char	*get_next_line(int	fd)
{
	static	char	*rem;
	char			*line;
	char			buffer[BS + 1];
	ssize_t			bytes;
	char			*temp;

	if (BS <= 0)
		return (NULL);
	while (1)
	{
		if (rem && strchr(rem, '\n'))
		{
			line = get_line(rem);
			rem = keep_rem(&rem);
			return (line);
		}
		bytes = read(fd, buffer, BS);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			temp = strjoin(rem, buffer);
			free(rem);
			rem = temp;
			continue ;
		}
		else if (bytes == -1)
			return (NULL);
	return (check_rem(&rem));
	}
}


int	main()
{
	int	fd;
	char	*line;

	fd = open("Makefile", O_RDONLY);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
}

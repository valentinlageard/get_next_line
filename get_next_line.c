#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

char	*ft_strcut_before(int i, char *str)
{
	int		j;
	char	*tmp;
	
	j = 0;
	if (!(tmp = (char *)malloc((ft_strlen(str) - i) * sizeof(char))))
		return (NULL);
	while (str[i + j + 1])
	{
		tmp[j] = str[i + j + 1];
		j++;
	}
	tmp[j] = 0;
	free(str);
	return (tmp);
}

int		ft_strcpy_woc(char *str, char **line, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		line[0][i] = str[i];
		i++;
	}
	line[0][i] = 0;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	int			sz_read;
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	
	if (!str)
		str = ft_strdup("");
	if (!ft_strchr(str, '\n'))
	{
		while ((sz_read = read(fd, buff, BUFFER_SIZE)) > 0)
		{
			buff[sz_read] = 0;
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
			if (ft_strchr(str, '\n'))
				break ;
		}
	}
	if (sz_read < 0 || line == NULL)
		return (-1);
	str = ft_strcut_before(ft_strcpy_woc(str, line, '\n'), str);
	if (sz_read == 0 && !str[0])
		return (0);
	return (1);
}

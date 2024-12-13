/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olopez-s <olopez-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:17:03 by olopez-s          #+#    #+#             */
/*   Updated: 2024/11/30 03:17:03 by olopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_delline(char *buffer)
{
	int		i;
	char	*newbuffer;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	newbuffer = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
	free(buffer);
	return (newbuffer);
}

static char	*ft_readline(int fd, char *buffer)
{
	char	*temp;
	int		i;

	i = 1;
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (free(temp), NULL);
		buffer[0] = '\0';
	}
	while (i > 0 && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1)
			return (free(temp), free(buffer), NULL);
		temp[i] = '\0';
		buffer = ft_strjoin_free(buffer, temp);
		if (!buffer)
			return (free(temp), free(buffer), NULL);
	}
	return (free(temp), buffer);
}

static char	*ft_retline(char *buffer)
{
	int		i;
	char	*readl;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	readl = ft_substr(buffer, 0, i);
	return (readl);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*readline;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = ft_readline(fd, buffer);
	if (!buffer)
		return (NULL);
	readline = ft_retline(buffer);
	if (readline[0] == '\0')
	{
		free (buffer);
		free (readline);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_delline(buffer);
	return (readline);
}

/*
 int	main(void)
{
	int		fd;
	char	*text;

	fd = open("lol.txt", O_RDONLY);
	text = get_next_line(fd);
	while (text)
	{
		printf("%s", text);
		free(text);
		text = get_next_line(fd);
	}
	free(text);
	close(fd);
	return(0);
}
*/
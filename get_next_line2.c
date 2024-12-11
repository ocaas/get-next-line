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

#include "get_next_line2.h"

static char	*ft_delline(char *buffer)
{
	int		i;
	char	*newbuffer;
	
	i = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if(!buffer[i])
		return(NULL);
	if(buffer[i] == '\n')
		i++;
	newbuffer = ft_substr(buffer, i, ft_strlen(buffer) - i);
	if(!newbuffer)
		return(free(buffer), NULL);
	free(buffer);
	return(newbuffer);
}

static char *ft_readline(int fd, char *buffer)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char)* BUFFER_SIZE + 1);
	if (!temp)
		return(NULL);
	if(!buffer)
	{
		buffer = malloc(sizeof(char)* 1);
		if(!buffer)
			return(free(temp), NULL);
		buffer[0] = '\0';
	}
	while (i > 0 && !ft_strchr(buffer, '\n')) // i > 0 - nuevo
	{
		i = read(fd, temp, BUFFER_SIZE);
		if(i == -1)
			return(free(temp), free(buffer), NULL);
		temp[i] = '\0';
		buffer = ft_strjoin_free(buffer, temp);
		if (!buffer)
			return(free(temp), free(buffer), NULL);
	}
	return(free(temp), buffer);
}
		// if (i == 0)
		// 	return(free(temp), buffer);

static char *ft_retline(char *buffer)
{
	int i;
	char *readl;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	readl = ft_substr(buffer, 0, i);
	return(readl);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffer;
	char	*readline;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = ft_readline(fd, buffer);
	if(!buffer)
		return (NULL);
	readline = ft_retline(buffer);
	if (readline[0] == '\0')
	{
		free(buffer);
		free(readline);
		buffer = NULL;
		return(NULL);
	}
	buffer = ft_delline(buffer);
	return(readline);
}

 int	main(void)
{
	int		fd;
	char	*text;

	fd = open("lol.txt", O_RDONLY);
	text = ft_get_next_line(fd);
	while (text)
	{
		printf("%s", text);
		free(text);
		text = ft_get_next_line(fd);
	}
	free(text);
	close(fd);
	return(0);
}
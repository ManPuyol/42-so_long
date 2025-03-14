/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:26:28 by manorteg          #+#    #+#             */
/*   Updated: 2024/11/09 14:53:50 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strextend(char *s1, size_t size, int *acc)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(s1) + size + 1), sizeof(char));
	if (!str)
		return (free(str), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	(*acc)++;
	free(s1);
	return (str);
}

static int	read_line_from_fd(int fd, t_buffer *buffers, char **line)
{
	int				line_pos;
	int				acc;
	char			c;

	line_pos = 0;
	acc = 1;
	while (1)
	{
		if (buffers[fd].position >= buffers[fd].bytes_read)
		{
			buffers[fd].position = 0;
			buffers[fd].bytes_read = read(fd, buffers[fd].content, BUFFER_SIZE);
			if (buffers[fd].bytes_read == 0)
				break ;
			else if (buffers[fd].bytes_read < 0)
				return (-1);
		}
		if (line_pos == ((MAX_LINE_LENGTH) * acc))
			*line = ft_strextend(*line, MAX_LINE_LENGTH, &acc);
		c = buffers[fd].content[buffers[fd].position++];
		(*line)[line_pos++] = c;
		if (c == '\n')
			break ;
	}
	return (line_pos);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffers[MAX_FD];
	char			*line;
	char			*next_line;
	int				line_pos;

	line_pos = 0;
	line = ft_calloc(MAX_LINE_LENGTH + 1, sizeof(char));
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || !line)
		return (free(line), NULL);
	line_pos = read_line_from_fd(fd, buffers, &line);
	if (line_pos <= 0)
		return (free(line), NULL);
	next_line = ft_strdup(line);
	free(line);
	return (next_line);
}
//one_line_no_nl.txt
//giant_line.txt
// int main (void)
// {
// 	int fd = open(
// "/home/manorteg/francinette/tests/get_next_line/fsoares/giant_line.txt"
// , O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("Line : %s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
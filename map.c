#include "fdf.h"

int	ft_define_map_width(char *line)
{
	char	**cols;
	int	width;

	width = 0;
	cols = ft_split(line, ' ');
	if (!cols)
		return (-1);
	while(cols[width])
		width++;
	ft_free_split(cols, width);
	return (width);
}

int	ft_define_map(t_map *map, char *file_name)
{
	int	fd;
	char	*line;

	if (!ft_strnstr(file_name, ".fdf", ft_strlen(file_name)))
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	map->height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->width = ft_define_map_width(line);
		printf("%s", line);
		free(line);
		map->height++;
	}
	close(fd);
	printf("height: %d\n", map->height);
	printf("width: %d\n", map->width);
	return (0);
}

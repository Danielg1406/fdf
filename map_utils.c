//TODO: Add 42 header
#include "fdf.h"

int	open_file(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_define_map_width(char *line)
{
	char	**cols;
	char	*trimmed_line;
	int		width;

	width = 0;
	trimmed_line = ft_strtrim(line, " \n");
	if (!trimmed_line)
		return (-1);
	cols = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!cols)
		return (-1);
	while (cols[width])
		width++;
	ft_free_split(cols, width);
	return (width);
}

int	calculate_map_dimensions(t_map *map, const char *file_name)
{
	int		fd;
	char	*line;

	fd = open_file(file_name);
	if (fd == -1)
		return (1);
	map->height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map->height == 0)
			map->width = ft_define_map_width(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

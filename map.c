#include "fdf.h"

int	ft_define_map(t_map *map, char *file_name)
{
	int	fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	map->height = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		map->height++;
	}
	close(fd);
	return (0);
}

#include "fdf.h"

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
		printf("%s", line);
		free(line);
		map->height++;
	}
	close(fd);
	printf("height: %d\n", map->height);
	return (0);
}

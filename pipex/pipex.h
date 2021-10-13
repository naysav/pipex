#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

void	display_error(char *str);
char	*dup_up2_n(char *str, unsigned int n);
int		find_nbr_char(char *str, char c);
char	*path_join(char *path, char *bin);

#endif
#include "../inc/cp_abe.h"
#include <unistd.h>

void	parse_args(char **argv, int *file_index, int *n_attrs, int *n_rep)
{
	*file_index = ft_atoi(argv[1]);
	*n_attrs = ft_atoi(argv[2]);
	*n_rep = ft_atoi(argv[3]);
	if (*file_index <= 0 || *file_index > 50)
		*file_index = 1;
	if (*n_attrs <= 0 || *n_attrs > 50)
		*n_attrs = 5;
	if (*n_rep <= 0 || *n_rep > 50)
		*n_rep = 20;
}

useconds_t	crypt_pdf(int file_index, int n_attrs, int n_rep, int logfile)
{
	useconds_t start_dec_time;
	useconds_t end_dec_time = 0;
	int i = 0;
	while (i++ < n_rep)
	{
		
		ft_putstr_fd("Starting decryption...\n", logfile);
		start_dec_time = get_time();
		decrypt_pdf(file_index, n_attrs);
		end_dec_time += get_time() - (start_dec_time + end_dec_time);
		ft_putstr_fd("Decrypted file from file_", logfile);
		ft_putnbr_fd(file_index, logfile);
		ft_putstr_fd(".\n", logfile);
	}
	printf("Decryption: %0.3lf seconds.\n", (double)(end_dec_time) / (1000));
	return (end_dec_time);
}

int	main(int argc, char **argv)
{
	int			file_index;
	int			n_attrs;
	int			n_rep;
	int			logfile;
	if (argc != 4)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd("cp_abe <file_index> <n_attributes> <n_repetitions>\n", 2);
		return (1);
	}
	parse_args(argv, &file_index, &n_attrs, &n_rep);
	logfile = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	printf("Job done with %d attribute(s) and %d repetition(s)\n", n_attrs, n_rep);
	crypt_pdf(file_index, n_attrs, n_rep, logfile);
	close(logfile);
	return (0);
}
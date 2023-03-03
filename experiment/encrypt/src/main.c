#include "../inc/cp_abe.h"
#include <unistd.h>

void	parse_args(char **argv, int *file_index, int *n_attrs, int *n_rep)
{
	*file_index = ft_atoi(argv[1]);
	*n_attrs = ft_atoi(argv[2]);
	*n_rep = ft_atoi(argv[3]);
	if (*file_index <= 0 || *file_index > 50)
		*file_index = 5;
	if (*n_attrs <= 0 || *n_attrs > 50)
		*n_attrs = 5;
	if (*n_rep <= 0 || *n_rep > 50)
		*n_rep = 20;
}

useconds_t	create_dirs(void)
{
	useconds_t start_time;
	useconds_t end_time;
	system("rm -rf tests");
	system("mkdir -p tests/master");
	chdir("tests/master");
	start_time = get_time();
	end_time = 0;
	system("cpabe-setup");
	end_time += get_time() - (start_time + end_time);
	chdir("..");
	return end_time;
}

useconds_t	config_dirs(int n_usrs, int n_attrs)
{
	int		ij[2];
	char	*cmd;
	useconds_t start_time;
	useconds_t end_time;

	ij[0] = 0;
	start_time = get_time();
	end_time = 0;
	while (ij[0]++ < n_usrs)
	{
		cmd = wrap_cmd(ft_strdup("mkdir -p "), get_str("user_", ij[0]), NULL);
		system(cmd);
		free(cmd);
		cmd = wrap_cmd(ft_strdup("cp -r master/pub_key "), \
			get_str("user_", ij[0]), NULL);
		system(cmd);
		free(cmd);
		ij[1] = 0;
		cmd = wrap_cmd(ft_strdup("cpabe-keygen -o "), get_str("user_", ij[0]), \
			ft_strdup("/priv master/pub_key master/master_key"));
		while (ij[1]++ < n_attrs)
			cmd = wrap_cmd(cmd, ft_strdup(" "), get_str("attr_", ij[1]));
		system(cmd);
		end_time += get_time() - (start_time + end_time);
		free(cmd);
	}
	return end_time;
}

useconds_t	crypt_pdf(int file_index, int n_attrs, int n_rep, int logfile)
{
	int			ij[2];
	useconds_t start_enc_time;
	useconds_t end_enc_time;

	ij[0] = 0;
	end_enc_time = 0;

	while (ij[0]++ < n_rep)
	{
		ft_putstr_fd("Starting encryption no. ", logfile);
		ft_putnbr_fd(ij[0], logfile);
		ft_putstr_fd("...\n", logfile);
		start_enc_time = get_time();
		encrypt_pdf(file_index, n_attrs);
		end_enc_time += get_time() - (start_enc_time + end_enc_time);
		ft_putstr_fd("Encryption complete.\n", logfile);
	}
	printf("\nEncryption: %0.3lf seconds\n", (double)(end_enc_time) / (1000));
	return (end_enc_time);
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
	printf("Job done with %d attribute(s) and %d repetition(s)", n_attrs, n_rep);
	crypt_pdf(file_index, n_attrs, n_rep, logfile);
	close(logfile);
	return (0);
}
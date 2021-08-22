#ifndef FORMAT_H
# define FORMAT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <curl/curl.h>
# include <json-c/json.h>

char	*get_user(char *login, char *token);

char	*get_token(char *uid, char *secret);

#endif

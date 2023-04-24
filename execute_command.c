/**
 * we modify the function to to search for command in the PATH environment variable
 */
void execute_command(char **args)
{
	char *command = NULL;
	char *path, *dir, *cmd;

	if (args)
	{
		command = args[0];
		if (strchr(command, '/') != NULL)
			/**
			 *  if the command includes a path, execve is called
			 *  with the command and arguments as it is
			 */
		{
			if (execve(command, args, eviron) == -1)
				perror("Error: ");
		}
		else // search the drectories specified
		{
			/**
			 * the getenv func is used to get the path value
			 * and strtok is used to split the value into
			 * individual directories
			 */
			path = getenv("PATH");
			if (path == NULL)
			{
				printf("Error: PATH not set\n");
				return;
			}
			dir = strtok(path, ":");
			while (dir != NULL)
			{
				/**
				 * for each directory the command is concatenated
				 * with the directory usibg sprintf to fotm a path to
				 * the command.
				 * the access function is used to check if the the path is a valid 
				 * executable file. if so, execve is called wit the dull path to the command and argument
				 */
				cmd = malloc(strlen(dir) + strlen(command) + 2);
				sprintf(cmd, "%s/%s", dir, command);
				if(access(cmd, X_OK) == 0)
				{
					execve(cmd, args, environ);
					perror("Error:");
				}
				free(cmd);
				dir = strtok(NULL, ":");
			}
			/* if no valid  command is found in any dir*/
			printf("Error: command not found\n");
			what are your thoughts? also how should we hndle the situation where the command does not exit and fork should not
				be called
}

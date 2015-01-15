#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	char path[32] = {0}, static_prefix[32] = {0};
	if(argc < 3)
	{
		printf("argc < 3, error exit \n");
		printf("useage: batch_delete /home/work_staton/www/ abc* \n");
		return -1;
	}
	snprintf(path, 32, "%s", argv[1]);
	snprintf(static_prefix, 32, "%s", argv[2]);

	char filename[64] = {0};
	DIR *dir = NULL;
    struct dirent *ptr = NULL;
	int ret = 0;
    dir = opendir(path);
    while((ptr = readdir(dir)))
    {

        if(strncmp(static_prefix, ptr->d_name, strlen(static_prefix)) == 0)
        {
        	printf("ptr->d_name=%s\n", ptr->d_name);

			snprintf(filename, 64, "%s/%s", path, ptr->d_name);
            ret = unlink(filename);
            //ret = remove(ptr->d_name);
			if(ret != 0)
			{
				perror("remove() error ");
				printf("ret=%d,errno=%d,filename=%s\n",ret,errno,filename);
			}
        }
    }
    closedir(dir);
	return 0;
}
